/*
 * ForceData.h
 *
 *  Created on: 21-Mar-2014
 *      Author: jaideep
 */

#ifndef FORCEDATA_H_
#define FORCEDATA_H_
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

namespace quarks
{
	namespace forces
	{
		enum force_type
		{
			UNIFORM_FORCE, DRAG_FORCE, NOISE_FORCE, VORTEX_FORCE, COLLISION_FORCE
		};
		class ForceData
		{
		public:
			ForceData(force_type type, Scalar amp, DirVec dir, openvdb::VectorGrid::Ptr gridPtr);
			virtual ~ForceData();
			Scalar getAmp() const;
			void setAmp(Scalar amp);
			const DirVec& getDir() const;
			void setDir(const DirVec& dir);
			const openvdb::VectorGrid::Ptr& getGridPtr() const;
			void setGridPtr(const openvdb::VectorGrid::Ptr& gridPtr);
			force_type getType() const;
			void setType(force_type type);

		private:
			force_type type;
			Scalar amp;
			DirVec dir;
			openvdb::VectorGrid::Ptr gridPtr;
		};
		typedef std::vector<forces::ForceData> ForceDataVector;
	} /* namespace forces */
} /* namespace quarks */
#endif /* FORCEDATA_H_ */
