#include "AttribManager.h"
#include "GU/GU_PrimPolySoup.h"
#include "GU/GU_PrimVDB.h"


namespace quarks::houdini {
    AttribManager::AttribManager() = default;

    AttribManager::~AttribManager() = default;

    void AttribManager::ExtractForceInfo(const GU_Detail *force, forces::ForceDataVector &force_data_vec) {
        const GEO_Primitive *prim;
        GA_FOR_ALL_PRIMITIVES(force, prim) {
            Scalar type_num = GetAttribScalar(force, prim, "type");
            const Scalar amp = GetAttribScalar(force, prim, "amp");
            const UT_Vector3 dir = GetAttribVector(force, prim, "dir");
            openvdb::VectorGrid::ConstPtr grid_ptr_;
            if (const auto *vdb_prim = dynamic_cast<const GU_PrimVDB *>(prim);
                vdb_prim && static_cast<forces::ForceType>(type_num) == forces::ForceType::VDB_FORCE) {
                grid_ptr_ = openvdb::gridConstPtrCast<openvdb::VectorGrid>(vdb_prim->getGridPtr());
            }
            forces::ForceData forceData(static_cast<forces::ForceType>(type_num), amp, dir, grid_ptr_);
            force_data_vec.push_back(forceData);
        }
    }

    void AttribManager::ExtractCollisionInfo(const GU_Detail *collision,
                                             collisions::CollisionDataVector &collision_data_vec) {
        const GEO_Primitive *prim;
        GA_FOR_ALL_PRIMITIVES(collision, prim) {
            if (const auto *vdb_prim = dynamic_cast<const GU_PrimVDB *>(prim)) {
                const Scalar gain_tangent = GetAttribScalar(collision, prim, "gainTangent");
                const Scalar gain_normal = GetAttribScalar(collision, prim, "gainNormal");
                const Scalar iso_val = GetAttribScalar(collision, prim, "isoVal");
                if (const openvdb::FloatGrid::ConstPtr grid_ptr_ = openvdb::gridConstPtrCast<openvdb::FloatGrid>(
                    vdb_prim->getGridPtr())) {
                    collisions::CollisionData collisionData(grid_ptr_, gain_tangent, gain_normal, iso_val);
                    collision_data_vec.push_back(collisionData);
                }
            }
        }
    }

    void AttribManager::ExtractSourceInfo(const GU_Detail *source,
                                          sources::SourceDataVector &source_data_vec) {
        const GA_ROHandleI handle_type(source, GA_ATTRIB_PRIMITIVE, "type");
        const GA_ROHandleF handle_rate(source, GA_ATTRIB_PRIMITIVE, "rate");
        const GA_ROHandleF handle_size(source, GA_ATTRIB_PRIMITIVE, "size");
        const GA_ROHandleV3 handle_pos(source, GA_ATTRIB_PRIMITIVE, "pos");
        const GA_ROHandleF handle_lifeExpectancy(source, GA_ATTRIB_PRIMITIVE, "lifeExpectancy");
        const GEO_Primitive *prim;
        GA_FOR_ALL_PRIMITIVES(source, prim) {
            const GA_Offset primOffset = prim->getMapOffset();

            int type_num(0);
            if (handle_type.isValid())
                type_num = handle_type.get(primOffset);
            fpreal rate(10);
            if (handle_rate.isValid())
                rate = handle_rate.get(primOffset);
            fpreal size(1);
            if (handle_size.isValid())
                size = handle_size.get(primOffset);
            UT_Vector3 pos;
            if (handle_pos.isValid())
                pos = handle_pos.get(primOffset);
            fpreal lifeExpectancy(10);
            if (handle_lifeExpectancy.isValid())
                lifeExpectancy = handle_lifeExpectancy.get(primOffset);

            // Only VDB sources have a grid
            if (const auto *vdb_prim = dynamic_cast<const GU_PrimVDB *>(prim);
                vdb_prim && static_cast<sources::SourceType>(type_num) == sources::SourceType::VDB_SOURCE) {
                openvdb::FloatGrid::ConstPtr grid_ptr_;
                grid_ptr_ = openvdb::gridConstPtrCast<openvdb::FloatGrid>(
                    vdb_prim->getGridPtr());
                if (grid_ptr_) {
                    pos = UT_Vector3(0, 0, 0);
                    sources::SourceData sourceData(static_cast<sources::SourceType>(type_num), static_cast<int>(rate),
                                                   pos, size,
                                                   lifeExpectancy,
                                                   grid_ptr_);
                    source_data_vec.push_back(sourceData);
                }
            } else {
                sources::SourceData sourceData(static_cast<sources::SourceType>(type_num), static_cast<int>(rate), pos,
                                               size,
                                               lifeExpectancy);
                source_data_vec.push_back(sourceData);
            }
        }
    }

    void AttribManager::ExtractSoftBodyInfo(const GU_Detail *soft_body_gdp,
                                            sources::SoftBodyDataVector &soft_body_data_vec) {
        const GA_ROHandleF handle_stiffness_constant(soft_body_gdp, GA_ATTRIB_PRIMITIVE, "spring_constant");
        const GA_ROHandleF handle_damping_constant(soft_body_gdp, GA_ATTRIB_PRIMITIVE, "damping_constant");
        const GA_ROHandleI handle_active(soft_body_gdp, GA_ATTRIB_PRIMITIVE, "active");
        const GA_ROHandleI handle_fixed(soft_body_gdp, GA_ATTRIB_POINT, "fixed");
        const GEO_Primitive *prim;

        // Loop through all soft body primitives
        GA_FOR_ALL_PRIMITIVES(soft_body_gdp, prim) {
            const GA_Offset primOffset = prim->getMapOffset();
            fpreal stiffness_constant(10);
            if (handle_stiffness_constant.isValid())
                stiffness_constant = handle_stiffness_constant.get(primOffset);
            fpreal damping_constant(10);
            if (handle_damping_constant.isValid())
                damping_constant = handle_damping_constant.get(primOffset);
            int active(1);
            if (handle_active.isValid())
                active = handle_active.get(primOffset);
            sources::SoftBodyData softBodyData(stiffness_constant, damping_constant, active);

            const auto *soupPrimPtr = dynamic_cast<const GU_PrimPolySoup *>(prim);
            // Create points
            for (int i = 0; i < soupPrimPtr->getVertexCount(); i++) {
                const GA_Offset ptoff = soupPrimPtr->getVertexOffset(i);
                const PosVec pos = soft_body_gdp->getPos3(ptoff);
                int fixed(0);
                if (handle_fixed.isValid())
                    fixed = handle_fixed.get(ptoff);
                softBodyData.InsertPoint(pos, fixed);
            }
            // Create springs between points
            for (int i = 0; i < soupPrimPtr->getPolygonCount(); i++) {
                const GA_Offset vtxoff_1 = soupPrimPtr->getPolygonVertexOffset(i, 0);
                const GA_Offset vtxoff_2 = soupPrimPtr->getPolygonVertexOffset(i, 1);
                const GA_Offset ptoff_1 = soupPrimPtr->getPointOffset(vtxoff_1);
                const GA_Offset ptoff_2 = soupPrimPtr->getPointOffset(vtxoff_2);
                softBodyData.InsertSpring(static_cast<int>(ptoff_1), static_cast<int>(ptoff_2));
            }
            soft_body_data_vec.push_back(softBodyData);
        }
    }

    template<typename T>
    T AttribManager::GetAttrib(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name) {
        GA_Offset primOffset = prim->getMapOffset();
        if (GA_ROHandleT<T> handle(gdp, GA_ATTRIB_PRIMITIVE, name); handle.isValid())
            return handle.get(primOffset);

        return T();
    }

    Scalar AttribManager::GetAttribScalar(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name) {
        return GetAttrib<fpreal>(gdp, prim, name);
    }

    UT_Vector3 AttribManager::GetAttribVector(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name) {
        return GetAttrib<UT_Vector3>(gdp, prim, name);
    }
} // namespace quarks::houdini
