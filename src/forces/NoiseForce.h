/*
 * DragForce.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef NOISEFORCE_H_
#define NOISEFORCE_H_
#include "Force.h"
namespace quarks
{
	namespace forces
	{
		class Noise_Force : public quarks::forces::Force
		{
		public:
			Noise_Force(Scalar amp)
			{
				amplitude = amp;
			};
			virtual ~Noise_Force(){};
			DirVec calculateFoce(PosVec pos, DirVec vel);
		private:
			Scalar amplitude;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* NOISEFORCE_H_ */
