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
		SourcePtr SourceFactory::getSource(SourceData sourceData)
		{
			int rate = sourceData.rate;
			PosVec pos = sourceData.pos;
			Scalar size = sourceData.size;
			Scalar lifeExpectancy = sourceData.lifeExpectancy;
			openvdb::FloatGrid::Ptr ptr = sourceData.gridPtr;
			switch (sourceData.type)
			{
			case SPHERE_SOURCE:
				return SourcePtr(new quarks::sources::SphereSource(rate, pos, size, lifeExpectancy));
				break;
			case VDB_SOURCE:
				return SourcePtr(new quarks::sources::VDB_Source(rate, ptr, lifeExpectancy));
				break;
			default:
				return SourcePtr(new quarks::sources::SphereSource(rate, pos, size, lifeExpectancy));
				break;
			}
		}
	} /* namespace sources */
} /* namespace quarks */
