/*
 * ForceManager.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "ForceManager.h"

namespace quarks
{
	namespace solver
	{
		void ForceManager::accumulateInternalForces(std::vector<Spring> & springs)
		{
			for (int i = 0; i < springs.size(); i++)
			{
				Spring& spring = springs[i];
				DirVec forceA, forceB;
				spring.calculateForce(forceA, forceB);
				Particle* nodeA = spring.nodeA;
				nodeA->force += forceA;
				Particle* nodeB = spring.nodeB;
				nodeB->force += forceB;
			}
		}
	} /* namespace solver */
} /* namespace quarks */
