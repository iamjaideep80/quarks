/*
 * Collision.cpp
 *
 *  Created on: 08-Mar-2014
 *      Author: jaideep
 */
#include "../base_types/CommonTypes.h"
#include "Collision.h"

namespace quarks
{
	namespace collisions
	{
		Collision::Collision(CollisionData collisionData)
		{
			gridPtr = collisionData.gridPtr;
			this->gainTangent = collisionData.gainTangent;
			this->gainNormal = collisionData.gainNormal;
			this->outerIsoVal = collisionData.isoVal;
		}
		Collision::~Collision()
		{
			// TODO Auto-generated destructor stub
		}
		const openvdb::FloatGrid::Ptr& Collision::getGridPtr() const
		{
			return gridPtr;
		}

		void Collision::applyCollision(const PosVec& oldPos, const DirVec& oldVel, PosVec& newPos,
				DirVec& newVel)
		{
			const openvdb::Vec3R ijk(newPos.x() / gridPtr->voxelSize().x(),
										newPos.y() / gridPtr->voxelSize().y(),
										newPos.z() / gridPtr->voxelSize().z());
			float sdfVal;
			openvdb::tools::PointSampler::sample(gridPtr->tree(), ijk, sdfVal);
			Scalar innerIsoVal = 0;
			if (sdfVal < outerIsoVal)
			{
				openvdb::Coord xyz(ijk.x(), ijk.y(), ijk.z());
				openvdb::math::Vec3d gradVal = openvdb::math::ISGradient<openvdb::math::CD_2ND>::result(
						gridPtr->getAccessor(), xyz);
				DirVec gradDir(gradVal.x(), gradVal.y(), gradVal.z());
				gradDir.normalize();
				Scalar normalDot = newVel.dot(gradDir);
				DirVec normalComp = normalDot * gradDir;
				DirVec tangentComp = newVel - normalComp;
				DirVec responseNormalComp = std::abs(normalDot) * gradDir;
				responseNormalComp = responseNormalComp * gainNormal;
				tangentComp = tangentComp * gainTangent;
				newVel = responseNormalComp + tangentComp;
			}
			if (sdfVal < innerIsoVal)
			{
				newPos = oldPos;
			}
		}
	}
} /* namespace quarks */
