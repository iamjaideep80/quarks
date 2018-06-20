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
		Noise_Force::Noise_Force(Scalar amp)
		{
			amplitude = amp;
		}
		Noise_Force::~Noise_Force()
		{
			// TODO Auto-generated destructor stub
		}
		DirVec Noise_Force::calculateFoce(PosVec pos, DirVec vel)
		{
//			DirVec oldVel = vel;
//			oldVel.normalize();
//			DirVec randomVel(drand48() - .5, drand48() - .5, drand48() - .5);
//			randomVel.normalize();
//			DirVec newVel = 0.5 * oldVel + 0.5 * randomVel;
//			newVel.normalize();
//			return amplitude * newVel;
			return vel;
		}
	} /* namespace forces */
} /* namespace quarks */
