/*
 * VDBForce.cpp
 *
 *  Created on: 08-Mar-2014
 *      Author: jaideep
 */
#include "VDBForce.h"
namespace quarks
{
	namespace forces
	{
		VDB_Force::VDB_Force(Scalar amp, DirVec dir, openvdb::VectorGrid::Ptr ptr)
		{
			amplitude = amp;
			gridPtr = ptr;
			// TODO Auto-generated constructor stub
		}
		VDB_Force::~VDB_Force()
		{
			// TODO Auto-generated destructor stub
		}
		DirVec VDB_Force::calculateFoce(PosVec pos, DirVec vel)
		{
			const openvdb::Vec3R ijk(pos.x() / gridPtr->voxelSize().x(), pos.y() / gridPtr->voxelSize().y(),
										pos.z() / gridPtr->voxelSize().z());
			openvdb::Vec3f val(1,2,3);
			openvdb::tools::PointSampler::sample(gridPtr->tree(), ijk, val);
			DirVec output(amplitude * val.x(), amplitude * val.y(), amplitude * val.z());
			return output;
		}
	} /* namespace forces */
} /* namespace quarks */
