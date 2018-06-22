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

		ForceManager::ForceManager()
		{
			// TODO Auto-generated constructor stub

		}

		ForceManager::~ForceManager()
		{
			// TODO Auto-generated destructor stub
		}
		void ForceManager::addForce(quarks::forces::Force* f)
		{
			forces.push_back(f);
		}
		void ForceManager::clearForces()
		{
			forces.clear();
		}
		void ForceManager::accumulateExternalForces(std::vector<Particle> & particles)
		{
			for (int i = 0; i < particles.size(); i++)
			{
				Particle& particle = particles[i];
				if(particle.life > particle.lifeExpectancy)
					continue;
				particle.force = 0;
				for (int j = 0; j < forces.size(); j++)
					particle.force += forces[j]->calculateFoce(particle.position,particle.velocity);
			}
		}
		void ForceManager::accumulateInternalForces(const std::vector<Spring*> & springs)
		{
			for (int i = 0; i < springs.size(); i++)
			{
				Spring* spring = springs[i];
				DirVec forceA, forceB;
				spring->calculateForce(forceA, forceB);
				Particle* nodeA = spring->nodeA;
				nodeA->force = (nodeA->force + forceA);
				Particle* nodeB = spring->nodeB;
				nodeB->force = (nodeB->force + forceB);
			}
		}

		void ForceManager::accumulateForces(std::vector<Particle>& particles,
				const std::vector<Spring*>& springs)
		{
			accumulateExternalForces(particles);
			accumulateInternalForces(springs);
		}

	} /* namespace solver */
} /* namespace quarks */
