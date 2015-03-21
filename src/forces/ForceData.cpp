/*
 * ForceData.cpp
 *
 *  Created on: 21-Mar-2014
 *      Author: jaideep
 */

#include "ForceData.h"

namespace quarks
{
	namespace forces
	{

		ForceData::ForceData(force_type type, Scalar amp, DirVec dir, openvdb::VectorGrid::Ptr gridPtr) :
				type(type), amp(amp), dir(dir), gridPtr(gridPtr)
		{
		}

		ForceData::~ForceData()
		{
			// TODO Auto-generated destructor stub
		}

		Scalar ForceData::getAmp() const
		{
			return amp;
		}

		void ForceData::setAmp(Scalar amp)
		{
			this->amp = amp;
		}

		const DirVec& ForceData::getDir() const
		{
			return dir;
		}

		void ForceData::setDir(const DirVec& dir)
		{
			this->dir = dir;
		}

		const openvdb::VectorGrid::Ptr& ForceData::getGridPtr() const
		{
			return gridPtr;
		}

		void ForceData::setGridPtr(const openvdb::VectorGrid::Ptr& gridPtr)
		{
			this->gridPtr = gridPtr;
		}

		force_type ForceData::getType() const
		{
			return type;
		}

		void ForceData::setType(force_type type)
		{
			this->type = type;
		}

	} /* namespace forces */
} /* namespace quarks */
