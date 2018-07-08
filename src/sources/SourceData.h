/*
 * SourceData.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef SOURCEDATA_H_
#define SOURCEDATA_H_

#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

namespace quarks
{
	namespace sources
	{
		enum sourceType
		{
			SPHERE_SOURCE, VDB_SOURCE, SOFTBODY_SOURCE
		};
		struct SourceData
		{
			SourceData(sourceType type,
					int rate,
					PosVec pos,
					Scalar size,
					Scalar lifeExpectancy,
					openvdb::FloatGrid::Ptr gridPtr) :
					type(type),
					rate(rate),
					pos(pos),
					size(size),
					lifeExpectancy(lifeExpectancy),
					gridPtr(gridPtr)
					{};
			sourceType type;
			int rate;
			PosVec pos;
			Scalar size;
			Scalar lifeExpectancy;
			openvdb::FloatGrid::Ptr gridPtr;
		};
		typedef std::vector<SourceData> SourceDataVector;
	} /* namespace sources */
} /* namespace quarks */
#endif /* SOURCEDATA_H_ */
