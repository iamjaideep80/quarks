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
			GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(force,prim)
			{
				GA_ROAttributeRef attRef_dir = force->findNumericTuple(GA_ATTRIB_PRIMITIVE, "dir", 3, 3);
//				forces::force_type type = (forces::force_type )getAttribScalar(force, prim, "type");
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
			GEO_Primitive* prim;
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
			GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(source,prim)
			{
				GA_ROAttributeRef attRef_type = source->findNumericTuple(GA_ATTRIB_PRIMITIVE, "type", 1, 1);
				GA_ROAttributeRef attRef_rate = source->findNumericTuple(GA_ATTRIB_PRIMITIVE, "rate", 1, 1);
				GA_ROAttributeRef attRef_size = source->findNumericTuple(GA_ATTRIB_PRIMITIVE, "size", 1, 1);
				GA_ROAttributeRef attRef_pos = source->findNumericTuple(GA_ATTRIB_PRIMITIVE, "pos", 3, 3);
				GA_ROAttributeRef attRef_lifeExpectancy = source->findNumericTuple(GA_ATTRIB_PRIMITIVE,
																					"lifeExpectancy", 1, 1);
				GA_ROAttributeRef attRef_spring_constant = source->findNumericTuple(GA_ATTRIB_PRIMITIVE,
																					"spring_constant", 1, 1);
				GA_ROAttributeRef attRef_damping_constant = source->findNumericTuple(GA_ATTRIB_PRIMITIVE,
																						"damping_constant", 1,
																						1);
				int type;
				if (attRef_type.isValid())
					prim->get(attRef_type, type, 0);
				fpreal rate(10);
				if (attRef_rate.isValid())
					prim->get(attRef_rate, rate, 0);
				fpreal size(1);
				if (attRef_size.isValid())
					prim->get(attRef_size, size, 0);
				UT_Vector3 pos;
				if (attRef_pos.isValid())
					prim->get(attRef_pos, pos.data(), 3);
				fpreal lifeExpectancy(10);
				if (attRef_lifeExpectancy.isValid())
					prim->get(attRef_lifeExpectancy, lifeExpectancy, 0);
				fpreal spring_constant(10);
				if (attRef_spring_constant.isValid())
					prim->get(attRef_spring_constant, spring_constant, 0);
				fpreal damping_constant(10);
				if (attRef_damping_constant.isValid())
					prim->get(attRef_damping_constant, damping_constant, 0);
				openvdb::FloatGrid::Ptr gridPtr;
				GU_PrimVDB* vdb_prim = (GU_PrimVDB*) prim;
				if (vdb_prim && type == 1)
				{
					gridPtr = openvdb::gridPtrCast<openvdb::FloatGrid>(vdb_prim->getGridPtr());
				}
				sources::SourceData sourceData(sources::sourceType(type), rate, pos, size, lifeExpectancy,
												gridPtr);
				sourceDataVec.push_back(sourceData);
			}
		}

		void AttribManager::extractSoftBodyInfo(const GU_Detail* softBodyGDP,
				sources::SoftBodyDataVector& softBodyDataVec)
		{
			GEO_Primitive* prim;
			GA_FOR_ALL_PRIMITIVES(softBodyGDP,prim)
			{
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
				if (attRef_spring_constant.isValid())
					prim->get(attRef_spring_constant, spring_constant, 0);
				fpreal damping_constant(10);
				if (attRef_damping_constant.isValid())
					prim->get(attRef_damping_constant, damping_constant, 0);
				int active(1);
				if (attRef_active.isValid())
					prim->get(attRef_active, active, 0);
				sources::SoftBodyData softBodyData(spring_constant, damping_constant, active);

				GU_PrimPolySoup* soupPrimPtr = (GU_PrimPolySoup*) prim;
				for (int i = 0; i < soupPrimPtr->getVertexCount(); i++)
				{
					GA_Offset ptoff = soupPrimPtr->getVertexOffset(i);
					PosVec pos = softBodyGDP->getPos3(ptoff);
//					const GEO_Point* pt = softBodyGDP->getGEOPoint(ptoff);
//					pt->get(attRef_fixed, fixed, 0);
					int fixed(0);
					if (aifFixed)
						aifFixed->get(attRef_fixed.getAttribute(), ptoff, &fixed, 1);
//					cout << "Point " << i << "  Fix : " << fixed << endl;
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

		Scalar AttribManager::getAttribScalar(const GU_Detail* gdp, GEO_Primitive* prim, char* name)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 1, 1);
			Scalar val;
			if (attRef_type.isValid())
				prim->get(attRef_type, val, 0);
			return val;
		}
		UT_Vector3 AttribManager::getAttribVector(const GU_Detail* gdp, GEO_Primitive* prim, char* name)
		{
			GA_ROAttributeRef attRef_type = gdp->findNumericTuple(GA_ATTRIB_PRIMITIVE, name, 3, 3);
			UT_Vector3 val;
			if (attRef_type.isValid())
				prim->get(attRef_type, val.data(), 3);
			return val;
		}

	} /* namespace houdini */
} /* namespace quarks */
