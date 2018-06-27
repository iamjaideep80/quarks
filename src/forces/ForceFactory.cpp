/*
 * ForceFactory.cpp
 *
 *  Created on: 01-Mar-2014
 *      Author: jaideep
 */
#include "ForceFactory.h"
namespace quarks
{
	namespace forces
	{
		ForcePtr ForceFactory::getForce(force_type type, Scalar amp, DirVec dir,
				openvdb::VectorGrid::Ptr gridPtr)
		{
			switch (type)
			{
			case 0:
				return ForcePtr(new quarks::forces::Uniform_Force(amp, dir));
				break;
			case 1:
				return ForcePtr(new quarks::forces::Drag_Force(amp));
				break;
			case 2:
				return ForcePtr(new quarks::forces::Noise_Force(amp));
				break;
			case 3:
				return ForcePtr(new quarks::forces::Vortex_Force(amp, dir));
				break;
			case 4:
				return ForcePtr(new quarks::forces::VDB_Force(amp, dir, gridPtr));
				break;
			default:
				return ForcePtr(new quarks::forces::Uniform_Force(amp, dir));
				break;
			}
		}
		ForcePtr ForceFactory::getForce(const ForceData& forceData)
		{
			return getForce(forceData.type, forceData.amp, forceData.dir,
							forceData.gridPtr);
		}
	} /* namespace forces */
} /* namespace quarks */
