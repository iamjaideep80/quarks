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
		ForcePtr ForceFactory::getForce(const ForceData& forceData)
		{
			switch (forceData.type)
			{
			case 0:
				return ForcePtr(new quarks::forces::Uniform_Force(forceData.amp, forceData.dir));
				break;
			case 1:
				return ForcePtr(new quarks::forces::Drag_Force(forceData.amp));
				break;
			case 2:
				return ForcePtr(new quarks::forces::Noise_Force(forceData.amp));
				break;
			case 3:
				return ForcePtr(new quarks::forces::Vortex_Force(forceData.amp, forceData.dir));
				break;
			case 4:
				return ForcePtr(new quarks::forces::VDB_Force(forceData.amp, forceData.dir, forceData.gridPtr));
				break;
			default:
				return ForcePtr(new quarks::forces::Uniform_Force(forceData.amp, forceData.dir));
				break;
			}
		}
	} /* namespace forces */
} /* namespace quarks */
