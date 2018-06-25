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
		void SourceManager::birthParticles(std::vector<Particle> & particles, unsigned int time)
		{
			for (int i = 0; i < sources.size(); i++)
			{
				quarks::sources::Source* srcPtr = sources[i];
				std::vector<PosVec> positions = srcPtr->requestPositions(time);
				for (int j = 0; j < srcPtr->getBirthRate(); j++)
				{
					particles.emplace_back(positions[j],
							srcPtr->getLifeExpectancy(),
							maxID);
					maxID++;
				}
			}
		}

	} /* namespace solver */
} /* namespace quarks */
