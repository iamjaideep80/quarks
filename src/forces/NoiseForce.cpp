/*
 * DragForce.cpp
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#include "NoiseForce.h"
namespace quarks
{
	namespace forces
	{
		DirVec Noise_Force::calculateFoce(PosVec pos, DirVec vel)
		{
			DirVec oldVel = vel;
			oldVel.normalize();
			DirVec randomVel(SYSdrand48() - .5, SYSdrand48() - .5, SYSdrand48() - .5);
			randomVel.normalize();
			DirVec newVel = 0.5 * oldVel + 0.5 * randomVel;
			newVel.normalize();
			return amplitude * newVel;
			return vel;
		}
	} /* namespace forces */
} /* namespace quarks */
