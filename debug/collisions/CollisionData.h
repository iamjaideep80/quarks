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

		class CollisionData
		{
		public:
			CollisionData(openvdb::FloatGrid::Ptr ptr, Scalar gainTangent, Scalar gainNormal, Scalar isoVal);
			virtual ~CollisionData();
			Scalar getGainNormal() const;
			void setGainNormal(Scalar gainNormal);
			Scalar getGainTangent() const;
			void setGainTangent(Scalar gainTangent);
			const openvdb::FloatGrid::Ptr& getGridPtr() const;
			void setGridPtr(const openvdb::FloatGrid::Ptr& gridPtr);
			Scalar getIsoVal() const;
			void setIsoVal(Scalar isoVal);

		private:
			openvdb::FloatGrid::Ptr gridPtr;
			Scalar gainTangent;
			Scalar gainNormal;
			Scalar isoVal;
		};
		typedef std::vector<CollisionData> CollisionDataVector;

	}
} /* namespace quarks */
#endif /* COLLISIONDATA_H_ */
