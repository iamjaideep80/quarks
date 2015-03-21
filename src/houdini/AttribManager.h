/*
 * AttribManager.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef ATTRIBMANAGER_H_
#define ATTRIBMANAGER_H_
#include "../sources/SourceData.h"
#include "../sources/SoftBodyData.h"
#include "../forces/ForceData.h"
#include "../collisions/CollisionData.h"
#include "GU/GU_Detail.h"
#include "GU/GU_PrimVDB.h"
namespace quarks
{
	namespace houdini
	{

		class AttribManager
		{
		public:
			AttribManager();
			virtual ~AttribManager();
			void extractSourceInfo(const GU_Detail* source, sources::SourceDataVector& sourceDataVec);
			void extractSoftBodyInfo(const GU_Detail* softBodyGDP,
					sources::SoftBodyDataVector& softBodyDataVec);
			void extractForceInfo(const GU_Detail* force, forces::ForceDataVector& forceDataVec);
			void extractCollisionInfo(const GU_Detail* collision,
					collisions::CollisionDataVector& collisionDataVec);
		private:
			Scalar getAttribScalar(const GU_Detail* gdp, GEO_Primitive* prim, char* name);
			UT_Vector3 getAttribVector(const GU_Detail* gdp, GEO_Primitive* prim, char* name);
		};

	} /* namespace houdini */
} /* namespace quarks */
#endif /* ATTRIBMANAGER_H_ */
