/*
 * SourceFactory.h
 *
 *  Created on: 01-Mar-2014
 *      Author: jaideep
 */
#ifndef SOURCEFACTORY_H_
#define SOURCEFACTORY_H_
#include "Source.h"
#include "SourceData.h"
#include "SphereSource.h"
#include "VDBSource.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/PointScatter.h>

namespace quarks
{
	namespace sources
	{
		class SourceFactory
		{
		public:
			SourceFactory(){};
			virtual ~SourceFactory(){};
			SourcePtr getSource(SourceData sourceData);
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* SOURCEFACTORY_H_ */
