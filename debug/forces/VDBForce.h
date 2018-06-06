/*
 * VDBForce.h
 *
 *  Created on: 08-Mar-2014
 *      Author: jaideep
 */
#ifndef VDBFORCE_H_
#define VDBFORCE_H_
#include "Force.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
namespace quarks
{
	namespace forces
	{
		class VDB_Force : public quarks::forces::Force
		{
		public:
			VDB_Force(Scalar amp, DirVec dir, openvdb::VectorGrid::Ptr ptr);
			virtual ~VDB_Force();
			DirVec calculateFoce(PosVec pos, DirVec vel);
		private:
			Scalar amplitude;
			openvdb::VectorGrid::Ptr gridPtr;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* VDBFORCE_H_ */
