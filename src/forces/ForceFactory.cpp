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
		ForceFactory::ForceFactory()
		{
			// TODO Auto-generated constructor stub
		}
		ForceFactory::~ForceFactory()
		{
			// TODO Auto-generated destructor stub
		}
		Force* ForceFactory::getForce(force_type type, Scalar amp, DirVec dir,
				openvdb::VectorGrid::Ptr gridPtr)
		{
			Force* force;
			switch (type)
			{
			case 0:
				force = new quarks::forces::Uniform_Force(amp, dir);
				break;
			case 1:
				force = new quarks::forces::Drag_Force(amp);
				break;
			case 2:
				force = new quarks::forces::Noise_Force(amp);
				break;
			case 3:
				force = new quarks::forces::Vortex_Force(amp, dir);
				break;
			case 4:
				force = new quarks::forces::VDB_Force(amp, dir, gridPtr);
				break;
			default:
				force = new quarks::forces::Uniform_Force(amp, dir);
				break;
			}
			return force;
		}
		Force* ForceFactory::getForce(const ForceData& forceData)
		{
			return getForce(forceData.type, forceData.amp, forceData.dir,
							forceData.gridPtr);
		}
	} /* namespace forces */
} /* namespace quarks */
