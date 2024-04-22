#ifndef ATTRIBMANAGER_H_
#define ATTRIBMANAGER_H_
#include "../sources/SourceData.h"
#include "../sources/SoftBodyData.h"
#include "../forces/ForceData.h"
#include "../collisions/CollisionData.h"
#include "GU/GU_Detail.h"


namespace quarks::houdini {
    class AttribManager {
    public:
        AttribManager();

        ~AttribManager();

        static void ExtractSourceInfo(const GU_Detail *source, sources::SourceDataVector &source_data_vec);

        static void ExtractSoftBodyInfo(const GU_Detail *soft_body_gdp,
                                        sources::SoftBodyDataVector &soft_body_data_vec);

        static void ExtractForceInfo(const GU_Detail *force, forces::ForceDataVector &force_data_vec);

        static void ExtractCollisionInfo(const GU_Detail *collision,
                                         collisions::CollisionDataVector &collision_data_vec);

    private:
        template<typename T>
        static T GetAttrib(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name);

        static Scalar GetAttribScalar(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name);

        static UT_Vector3 GetAttribVector(const GU_Detail *gdp, const GEO_Primitive *prim, const char *name);
    };
} // namespace quarks::houdini

#endif /* ATTRIBMANAGER_H_ */
