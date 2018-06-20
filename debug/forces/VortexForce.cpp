/*
 * UniformForce.cpp
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#include "VortexForce.h"
namespace quarks
{
	namespace forces
	{
		Vortex_Force::Vortex_Force(Scalar amp, DirVec dir)
		{
			amplitude = amp;
			direction = dir;
		}
		Vortex_Force::~Vortex_Force()
		{
			// TODO Auto-generated destructor stub
		}
		DirVec Vortex_Force::calculateFoce(PosVec pos, DirVec vel)
		{
			DirVec modPos = pos - dot(direction, pos) * direction;
			DirVec vortexVec = cross(modPos, direction);
			return amplitude * vortexVec;
		}
	} /* namespace forces */
} /* namespace quarks */
