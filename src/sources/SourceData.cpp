/*
 * SourceData.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "SourceData.h"

namespace quarks
{
	namespace sources
	{

		SourceData::SourceData(sourceType type, int rate, PosVec pos, Scalar size, Scalar lifeExpectancy,
				openvdb::FloatGrid::Ptr gridPtr) :
				type(type), rate(rate), pos(pos), size(size), lifeExpectancy(lifeExpectancy), gridPtr(gridPtr)
		{
		}

		SourceData::~SourceData()
		{
			// TODO Auto-generated destructor stub
		}

		const openvdb::FloatGrid::Ptr& SourceData::getGridPtr() const
		{
			return gridPtr;
		}

		void SourceData::setGridPtr(const openvdb::FloatGrid::Ptr& gridPtr)
		{
			this->gridPtr = gridPtr;
		}

		Scalar SourceData::getLifeExpectancy() const
		{
			return lifeExpectancy;
		}

		void SourceData::setLifeExpectancy(Scalar lifeExpectancy)
		{
			this->lifeExpectancy = lifeExpectancy;
		}

		const PosVec& SourceData::getPos() const
		{
			return pos;
		}

		void SourceData::setPos(const PosVec& pos)
		{
			this->pos = pos;
		}

		int SourceData::getRate() const
		{
			return rate;
		}

		void SourceData::setRate(int rate)
		{
			this->rate = rate;
		}

		Scalar SourceData::getSize() const
		{
			return size;
		}

		void SourceData::setSize(Scalar size)
		{
			this->size = size;
		}

		sourceType SourceData::getType() const
		{
			return type;
		}

		void SourceData::setType(sourceType type)
		{
			this->type = type;
		}
	} /* namespace sources */
} /* namespace quarks */
