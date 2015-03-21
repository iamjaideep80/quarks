/*
 * UniformForce.cpp
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#include "UniformForce.h"
namespace quarks
{
	namespace forces
	{
		Uniform_Force::Uniform_Force(Scalar amp, DirVec dir)
		{
			amplitude = amp;
			direction = dir;
		}
		Uniform_Force::~Uniform_Force()
		{
			// TODO Auto-generated destructor stub
		}
		DirVec Uniform_Force::calculateFoce(PosVec pos, DirVec vel)
		{
			return amplitude * direction;
		}
	} /* namespace forces */
} /* namespace quarks */
