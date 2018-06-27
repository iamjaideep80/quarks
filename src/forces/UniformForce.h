/*
 * UniformForce.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef UNIFORMFORCE_H_
#define UNIFORMFORCE_H_
#include "Force.h"
namespace quarks
{
	namespace forces
	{
		class Uniform_Force : public quarks::forces::Force
		{
		public:
			Uniform_Force(Scalar amp, DirVec dir)
			{
				amplitude = amp;
				direction = dir;
			}
			virtual ~Uniform_Force(){};
			inline DirVec calculateFoce(PosVec pos, DirVec vel)
			{
				return amplitude * direction;
			}
		private:
			Scalar amplitude;
			DirVec direction;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* UNIFORMFORCE_H_ */
