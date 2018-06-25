/*
 * CollisionData.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef COLLISIONDATA_H_
#define COLLISIONDATA_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
namespace quarks
{
	namespace collisions
	{

		struct CollisionData
		{
			CollisionData(openvdb::FloatGrid::Ptr gridPtr,
					Scalar gainTangent,
					Scalar gainNormal,
					Scalar isoVal) :
					gridPtr(gridPtr),
					gainTangent(gainTangent),
					gainNormal(gainNormal),
					isoVal(isoVal)
					{};
			openvdb::FloatGrid::Ptr gridPtr;
			Scalar gainTangent;
			Scalar gainNormal;
			Scalar isoVal;
		};
		typedef std::vector<CollisionData> CollisionDataVector;

	}
} /* namespace quarks */
#endif /* COLLISIONDATA_H_ */
