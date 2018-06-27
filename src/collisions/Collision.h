/*
 * Collision.h
 *
 *  Created on: 08-Mar-2014
 *      Author: jaideep
 */
#ifndef COLLISION_H_
#define COLLISION_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <openvdb/math/Operators.h>
#include <openvdb/math/FiniteDifference.h>
#include "CollisionData.h"
namespace quarks
{
	namespace collisions
	{
		class Collision
		{
		public:
			Collision(CollisionData	 collisionData);
			virtual ~Collision(){};
			inline const openvdb::FloatGrid::Ptr& getGridPtr() const
			{
				return gridPtr;
			}
			void applyCollision(const PosVec& oldPos, const DirVec& oldVel, PosVec& newPos, DirVec& newVel);
		private:
			openvdb::FloatGrid::Ptr gridPtr;
			Scalar gainTangent;
			Scalar gainNormal;
			Scalar outerIsoVal;
		};
	}
} /* namespace quarks */
#endif /* COLLISION_H_ */
