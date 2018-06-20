/*
 * UniformForce.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef VORTEXFORCE_H_
#define VORTEXFORCE_H_
#include "Force.h"
namespace quarks
{
	namespace forces
	{
		class Vortex_Force : public quarks::forces::Force
		{
		public:
			Vortex_Force(Scalar amp, DirVec dir);
			virtual ~Vortex_Force();
			DirVec calculateFoce(PosVec pos, DirVec vel);
		private:
			Scalar amplitude;
			DirVec direction;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* VORTEXFORCE_H_ */
