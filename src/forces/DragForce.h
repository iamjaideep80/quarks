/*
 * DragForce.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef DRAGFORCE_H_
#define DRAGFORCE_H_
#include "Force.h"
namespace quarks
{
	namespace forces
	{
		class Drag_Force : public quarks::forces::Force
		{
		public:
			inline Drag_Force(Scalar amp)
			{
				amplitude = amp;
			}
			inline virtual ~Drag_Force(){};
			inline DirVec calculateFoce(PosVec pos, DirVec vel)
			{
				return -1 * amplitude * vel;
			}
		private:
			Scalar amplitude;
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* DRAGFORCE_H_ */
