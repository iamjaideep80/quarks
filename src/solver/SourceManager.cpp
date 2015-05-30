/*
 * SourceManager.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "SourceManager.h"
#include "../sources/SoftBodySource.h"
namespace quarks
{
	namespace solver
	{

		SourceManager::SourceManager()
		{
			sources.clear();
			maxID = 0;
		}

		SourceManager::~SourceManager()
		{
			// TODO Auto-generated destructor stub
		}
		void SourceManager::addSource(quarks::sources::Source* f)
		{
			sources.push_back(f);
		}
		void SourceManager::clearSources()
		{
			sources.clear();
		}
		void SourceManager::birthParticles(std::vector<Particle*> & particles, unsigned int time)
		{
			for (int i = 0; i < sources.size(); i++)
			{
				quarks::sources::Source* srcPtr = sources[i];
				std::vector<PosVec> positions = srcPtr->requestPositions(time);
//				std::vector<Particle*> source_particles;
				for (int j = 0; j < srcPtr->getBirthRate(); j++)
				{
					PosVec initPos(positions[j][0], positions[j][1], positions[j][2]);
					DirVec initVel(0, 0, 0);
					Scalar initLifeExpectancy = srcPtr->getLifeExpectancy();
					Particle* part = birthSingleParticle(initPos, initVel, initLifeExpectancy);
					particles.push_back(part);
//					source_particles.push_back(part);
				}
			}
		}
		Particle* SourceManager::birthSingleParticle(PosVec initPos, DirVec initVel,
				Scalar initLifeExpectancy)
		{
			Particle* p = new Particle(initLifeExpectancy, maxID);
			maxID++;
			p->setPosition(initPos);
			p->setVelocity(initVel);
			return p;
		}

	} /* namespace solver */
} /* namespace quarks */
