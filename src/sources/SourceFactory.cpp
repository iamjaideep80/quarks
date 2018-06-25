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
			int rate = sourceData.rate;
			PosVec pos = sourceData.pos;
			Scalar size = sourceData.size;
			Scalar lifeExpectancy = sourceData.lifeExpectancy;
			openvdb::FloatGrid::Ptr ptr = sourceData.gridPtr;
			Source* source;
			switch (sourceData.type)
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
