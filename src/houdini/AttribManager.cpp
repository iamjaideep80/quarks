/*
 * AttribManager.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "AttribManager.h"
#include "GU/GU_PrimPolySoup.h"

namespace quarks
{
	namespace houdini
	{

		AttribManager::AttribManager()
		{
		}

		AttribManager::~AttribManager()
		{
		}
		void AttribManager::extractForceInfo(const GU_Detail* force, forces::ForceDataVector& forceDataVec)
		{
			const GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(force,prim)
			{
				GA_ROAttributeRef attRef_dir = force->findNumericTuple(GA_ATTRIB_PRIMITIVE, "dir", 3, 3);
				Scalar type = getAttribScalar(force, prim, "type");
				Scalar amp = getAttribScalar(force, prim, "amp");
				UT_Vector3 dir = getAttribVector(force, prim, "dir");
				openvdb::VectorGrid::Ptr gridPtr;
				GU_PrimVDB* vdb_prim = (GU_PrimVDB*) prim;
				if (vdb_prim && type == 4)
				{
					gridPtr = openvdb::gridPtrCast<openvdb::VectorGrid>(vdb_prim->getGridPtr());
				}
				forces::ForceData forceData(forces::force_type(type), amp, dir, gridPtr);
				forceDataVec.push_back(forceData);
			}
		}

		void AttribManager::extractCollisionInfo(const GU_Detail* collision,
				collisions::CollisionDataVector& collisionDataVec)
		{
			const GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(collision,prim)
			{
				GU_PrimVDB* vdb_prim = (GU_PrimVDB*) prim;
				if (vdb_prim)
				{
					Scalar gainTangent = getAttribScalar(collision, prim, "gainTangent");
					Scalar gainNormal = getAttribScalar(collision, prim, "gainNormal");
					Scalar isoVal = getAttribScalar(collision, prim, "isoVal");
					openvdb::FloatGrid::Ptr gridPtr = openvdb::gridPtrCast<openvdb::FloatGrid>(
							vdb_prim->getGridPtr());
					if (gridPtr)
					{
						collisions::CollisionData collisionData(gridPtr, gainTangent, gainNormal, isoVal);
						collisionDataVec.push_back(collisionData);
					}
				}
			}
		}

		void AttribManager::extractSourceInfo(const GU_Detail* source,
				sources::SourceDataVector& sourceDataVec)
		{
			const GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(source,prim)
			{
				GA_Offset primOffset = prim->getMapOffset();
				GA_ROHandleI handle_type(source, GA_ATTRIB_PRIMITIVE, "type");
				GA_ROHandleF handle_rate(source, GA_ATTRIB_PRIMITIVE, "rate");
				GA_ROHandleF handle_size(source, GA_ATTRIB_PRIMITIVE, "size");
				GA_ROHandleV3 handle_pos(source, GA_ATTRIB_PRIMITIVE, "pos");
				GA_ROHandleF handle_lifeExpectancy(source, GA_ATTRIB_PRIMITIVE, "lifeExpectancy");
				GA_ROHandleF handle_spring_constant(source, GA_ATTRIB_PRIMITIVE, "spring_constant");
				GA_ROHandleF handle_damping_constant(source, GA_ATTRIB_PRIMITIVE, "damping_constant");

				int type;
				if (handle_type.isValid())
					type = handle_type.get(primOffset);
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
				fpreal spring_constant(10);
				if (handle_spring_constant.isValid())
					spring_constant = handle_spring_constant.get(primOffset);
				fpreal damping_constant(10);
				if (handle_damping_constant.isValid())
					damping_constant = handle_damping_constant.get(primOffset);

				openvdb::FloatGrid::Ptr gridPtr;
				GU_PrimVDB* vdb_prim = (GU_PrimVDB*) prim;
				if (vdb_prim && type == 1)
				{
					gridPtr = openvdb::gridPtrCast<openvdb::FloatGrid>(vdb_prim->getGridPtr());
					if(gridPtr)
					{
						sources::SourceData sourceData(sources::sourceType(type), rate, pos, size, lifeExpectancy,
														gridPtr);
						sourceDataVec.push_back(sourceData);
					}
				}
			}
		}

		void AttribManager::extractSoftBodyInfo(const GU_Detail* softBodyGDP,
				sources::SoftBodyDataVector& softBodyDataVec)
		{
			const GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(softBodyGDP,prim)
			{
				GA_Offset primOffset = prim->getMapOffset();
				GA_ROHandleF handle_spring_constant(softBodyGDP, GA_ATTRIB_PRIMITIVE, "spring_constant");
				GA_ROHandleF handle_damping_constant(softBodyGDP, GA_ATTRIB_PRIMITIVE, "damping_constant");
				GA_ROHandleI handle_active(softBodyGDP, GA_ATTRIB_PRIMITIVE, "active");





				GA_ROAttributeRef attRef_spring_constant = softBodyGDP->findNumericTuple(GA_ATTRIB_PRIMITIVE,
																							"spring_constant",
																							1, 1);
				GA_ROAttributeRef attRef_damping_constant = softBodyGDP->findNumericTuple(
						GA_ATTRIB_PRIMITIVE, "damping_constant", 1, 1);
				GA_ROAttributeRef attRef_active = softBodyGDP->findIntTuple(GA_ATTRIB_PRIMITIVE, "active", 1,
																			1);
				GA_ROAttributeRef attRef_fixed = softBodyGDP->findIntTuple(GA_ATTRIB_POINT, "fixed", 1);
				const GA_AIFTuple *aifFixed = attRef_fixed.getAIFTuple();

				fpreal spring_constant(10);
				if (handle_spring_constant.isValid())
					spring_constant = handle_spring_constant.get(primOffset);
				fpreal damping_constant(10);
				if (handle_damping_constant.isValid())
					damping_constant = handle_damping_constant.get(primOffset);
				int active(1);
				if (handle_active.isValid())
					active = handle_active.get(primOffset);
				sources::SoftBodyData softBodyData(spring_constant, damping_constant, active);

				GU_PrimPolySoup* soupPrimPtr = (GU_PrimPolySoup*) prim;
				for (int i = 0; i < soupPrimPtr->getVertexCount(); i++)
				{
					GA_Offset ptoff = soupPrimPtr->getVertexOffset(i);
					PosVec pos = softBodyGDP->getPos3(ptoff);
					int fixed(0);
					if (aifFixed)
						aifFixed->get(attRef_fixed.getAttribute(), ptoff, &fixed, 1);
					softBodyData.insertPoint(pos, fixed);
				}
				for (int i = 0; i < soupPrimPtr->getPolygonCount(); i++)
				{
					GA_Offset vtxoff_1 = soupPrimPtr->getPolygonVertexOffset(i, 0);
					GA_Offset vtxoff_2 = soupPrimPtr->getPolygonVertexOffset(i, 1);
					GA_Offset ptoff_1 = soupPrimPtr->getPointOffset(vtxoff_1);
					GA_Offset ptoff_2 = soupPrimPtr->getPointOffset(vtxoff_2);
					softBodyData.insertSpring(ptoff_1, ptoff_2);
				}
				softBodyDataVec.push_back(softBodyData);

			}
		}

		Scalar AttribManager::getAttribScalar(const GU_Detail* gdp, const GEO_Primitive* prim, char* name)
		{
			GA_Offset primOffset = prim->getMapOffset();
			GA_ROHandleF handle(gdp, GA_ATTRIB_PRIMITIVE, name);
			if (handle.isValid())
				return handle.get(primOffset);
			else
				return 0;
		}
		UT_Vector3 AttribManager::getAttribVector(const GU_Detail* gdp, const GEO_Primitive* prim, char* name)
		{
			GA_Offset primOffset = prim->getMapOffset();
			GA_ROHandleV3 handle(gdp, GA_ATTRIB_PRIMITIVE, name);
			if (handle.isValid())
				return handle.get(primOffset);
			else
				return UT_Vector3();
		}

	} /* namespace houdini */
} /* namespace quarks */
