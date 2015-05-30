/*
 * SourceFactory.cpp
 *
 *  Created on: 01-Mar-2014
 *      Author: jaideep
 */
#include "SourceFactory.h"

namespace quarks
{
	namespace sources
	{
		SourceFactory::SourceFactory()
		{
			// TODO Auto-generated constructor stub
		}
		SourceFactory::~SourceFactory()
		{
			// TODO Auto-generated destructor stub
		}
		Source* SourceFactory::getSource(SourceData sourceData)
		{
			sourceType type = sourceData.getType();
			int rate = sourceData.getRate();
			PosVec pos = sourceData.getPos();
			Scalar size = sourceData.getSize();
			Scalar lifeExpectancy = sourceData.getLifeExpectancy();
			openvdb::FloatGrid::Ptr ptr = sourceData.getGridPtr();
			Source* source;
			switch (type)
			{
			case SPHERE_SOURCE:
				source = new quarks::sources::SphereSource(rate, pos, size, lifeExpectancy);
				break;
			case VDB_SOURCE:
				source = new quarks::sources::VDB_Source(rate, ptr, lifeExpectancy);
				break;
			default:
				source = new quarks::sources::SphereSource(rate, pos, size, lifeExpectancy);
				break;
			}
			return source;
		}
	} /* namespace sources */
} /* namespace quarks */
