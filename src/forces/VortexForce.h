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
			Vortex_Force(Scalar amp, DirVec dir)
			{
				amplitude = amp;
				direction = dir;
			}
			virtual ~Vortex_Force(){};
			inline DirVec calculateFoce(PosVec pos, DirVec vel)
			{
				DirVec modPos = pos - dot(direction, pos) * direction;
				return amplitude * cross(modPos, direction);
			}
		private:
			Scalar amplitude;
			DirVec direction;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* VORTEXFORCE_H_ */
