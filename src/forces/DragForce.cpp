/*
 * DragForce.cpp
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#include "DragForce.h"
namespace quarks
{
	namespace forces
	{
		Drag_Force::Drag_Force(Scalar amp)
		{
			amplitude = amp;
		}
		Drag_Force::~Drag_Force()
		{
			// TODO Auto-generated destructor stub
		}
		DirVec Drag_Force::calculateFoce(PosVec pos, DirVec vel)
		{
			return -1 * amplitude * vel;
		}
	} /* namespace forces */
} /* namespace quarks */
