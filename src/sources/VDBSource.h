/*
 * VDBSource.h
 *
 *  Created on: 09-Mar-2014
 *      Author: jaideep
 */
#ifndef VDBSOURCE_H_
#define VDBSOURCE_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/PointScatter.h>
#include "Source.h"
namespace quarks
{
	namespace sources
	{
		class VDB_Source : public quarks::sources::Source
		{
		public:
			VDB_Source(Scalar rate, openvdb::FloatGrid::Ptr ptr,Scalar lifeExpectancy);
			virtual ~VDB_Source();
			std::vector<PosVec> requestPositions(unsigned int time);
//			SpringMap requestSpringMap(unsigned int time);
		private:
			openvdb::FloatGrid::Ptr gridPtr;
		};
	} /* namespace sources */
} /* namespace quarks */
#endif /* VDBSOURCE_H_ */
