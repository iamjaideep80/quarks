/*
 * CollisionData.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "CollisionData.h"

namespace quarks
{
	namespace collisions
	{

		CollisionData::CollisionData(openvdb::FloatGrid::Ptr gridPtr, Scalar gainTangent, Scalar gainNormal,
				Scalar isoVal) :
				gridPtr(gridPtr), gainTangent(gainTangent), gainNormal(gainNormal), isoVal(isoVal)
		{
		}

		CollisionData::~CollisionData()
		{
			// TODO Auto-generated destructor stub
		}

		Scalar CollisionData::getGainNormal() const
		{
			return gainNormal;
		}

		void CollisionData::setGainNormal(Scalar gainNormal)
		{
			this->gainNormal = gainNormal;
		}

		Scalar CollisionData::getGainTangent() const
		{
			return gainTangent;
		}

		void CollisionData::setGainTangent(Scalar gainTangent)
		{
			this->gainTangent = gainTangent;
		}

		const openvdb::FloatGrid::Ptr& CollisionData::getGridPtr() const
		{
			return gridPtr;
		}

		void CollisionData::setGridPtr(const openvdb::FloatGrid::Ptr& gridPtr)
		{
			this->gridPtr = gridPtr;
		}

		Scalar CollisionData::getIsoVal() const
		{
			return isoVal;
		}

		void CollisionData::setIsoVal(Scalar isoVal)
		{
			this->isoVal = isoVal;
		}

	}
} /* namespace quarks */
