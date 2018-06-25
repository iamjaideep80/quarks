/*
 * SoftBodyManager.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "SoftBodyManager.h"
#include "../sources/SoftBodySource.h"
namespace quarks
{
	namespace solver
	{

		SoftBodyManager::SoftBodyManager()
		{
			softBodies.clear();
			maxID = 0;
		}

		SoftBodyManager::~SoftBodyManager()
		{
			// TODO Auto-generated destructor stub
		}
		void SoftBodyManager::addSoftBody(quarks::sources::SoftBodySourcePtr f)
		{
			softBodies.push_back(f);
		}
		void SoftBodyManager::clearSoftBodies()
		{
			softBodies.clear();
		}
		void SoftBodyManager::birthParticles(std::vector<Particle> & particles,
				std::vector<Spring> & springs, unsigned int time)
		{
			for (int softBodyNum = 0; softBodyNum < softBodies.size(); softBodyNum++)
			{
				quarks::sources::SoftBodySourcePtr srcPtr = softBodies[softBodyNum];
				if (!srcPtr->isActive())
					continue;
				std::vector<PosVec> positions = srcPtr->requestPositions(time);
				std::vector<bool> fixPoints = srcPtr->requestFixPoints(time);
				std::vector<Particle*> source_particles;
				for (int pointNum = 0; pointNum < srcPtr->getBirthRate(); pointNum++)
				{
					PosVec initPos(positions[pointNum][0], positions[pointNum][1], positions[pointNum][2]);
					Scalar initLifeExpectancy = srcPtr->getLifeExpectancy();
					particles.emplace_back(initPos,initLifeExpectancy,maxID,fixPoints[pointNum], softBodyNum, pointNum);
					source_particles.push_back(&(particles.back()));
					maxID++;
				}
				SpringMap springMap = srcPtr->requestSpringMap(time);
				for (SpringMap::iterator it = springMap.begin(); it != springMap.end(); ++it)
				{
					std::pair<int, int> nodePair = *it;
					Particle* nodeA = source_particles[nodePair.first];
					Particle* nodeB = source_particles[nodePair.second];
					DirVec vecAB = nodeA->position - nodeB->position;
					springs.emplace_back(nodeA, nodeB, vecAB.length(), srcPtr->getSpringConstant(),
							srcPtr->getDampingConstant());
				}
			}
		}
		PosVec SoftBodyManager::getConstraintPos(int softBodyNum, int pointNum)
		{
			return softBodies[softBodyNum]->requestPositions(0, pointNum);
		}
	} /* namespace solver */
} /* namespace quarks */
