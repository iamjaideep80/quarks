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
		class SourceData
		{
		public:
			SourceData(sourceType type, int rate, PosVec pos, Scalar size, Scalar lifeExpectancy,
					openvdb::FloatGrid::Ptr gridPtr);
			virtual ~SourceData();
			const openvdb::FloatGrid::Ptr& getGridPtr() const;
			void setGridPtr(const openvdb::FloatGrid::Ptr& gridPtr);
			Scalar getLifeExpectancy() const;
			void setLifeExpectancy(Scalar lifeExpectancy);
			const PosVec& getPos() const;
			void setPos(const PosVec& pos);
			int getRate() const;
			void setRate(int rate);
			Scalar getSize() const;
			void setSize(Scalar size);
			sourceType getType() const;
			void setType(sourceType type);

		private:
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
