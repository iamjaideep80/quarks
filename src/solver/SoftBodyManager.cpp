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
		void SoftBodyManager::addSoftBody(quarks::sources::SoftBodySource* f)
		{
			softBodies.push_back(f);
		}
		void SoftBodyManager::clearSoftBodies()
		{
			softBodies.clear();
		}
		void SoftBodyManager::birthParticles(std::vector<Particle> & particles,
				std::vector<Spring*> & springs, unsigned int time)
		{
			for (int softBodyNum = 0; softBodyNum < softBodies.size(); softBodyNum++)
			{
				quarks::sources::SoftBodySource* srcPtr = softBodies[softBodyNum];
				if (!srcPtr->isActive())
					continue;
				std::vector<PosVec> positions = srcPtr->requestPositions(time);
				std::vector<bool> fixPoints = srcPtr->requestFixPoints(time);
				std::vector<Particle> source_particles;
				for (int pointNum = 0; pointNum < srcPtr->getBirthRate(); pointNum++)
				{
					PosVec initPos(positions[pointNum][0], positions[pointNum][1], positions[pointNum][2]);
					Scalar initLifeExpectancy = srcPtr->getLifeExpectancy();
					Particle part = birthSingleParticle(initPos, initLifeExpectancy,
															fixPoints[pointNum], softBodyNum, pointNum);
					particles.push_back(part);
					source_particles.push_back(part);
				}
				quarks::sources::SoftBodySource* sbSrcPtr =
						static_cast<quarks::sources::SoftBodySource*>(srcPtr);
				SpringMap springMap = sbSrcPtr->requestSpringMap(time);
				for (SpringMap::iterator it = springMap.begin(); it != springMap.end(); ++it)
				{
					std::pair<int, int> nodePair = *it;
					Particle* nodeA = &source_particles[nodePair.first];
					std::cout << "nodeA : " << nodeA << std::endl;
					Particle* nodeB = &source_particles[nodePair.second];
					std::cout << "nodeB : " << nodeB << std::endl;
					DirVec vecAB = nodeA->position - nodeB->position;
					std::cout << "vecAB.length() : " << vecAB.length() << std::endl;
					Spring* spring = new Spring(nodeA, nodeB, vecAB.length(), sbSrcPtr->getSpringConstant(),
												sbSrcPtr->getDampingConstant());
					springs.push_back(spring);
				}
			}
		}
		Particle SoftBodyManager::birthSingleParticle(PosVec initPos,
				Scalar initLifeExpectancy, bool isFix, int softBodySourceNum, int softBodyPointNum)
		{
			Particle p(initPos,initLifeExpectancy, maxID);
			maxID++;
			p.isFixed = (isFix);
			p.softBodySourceNum = (softBodySourceNum);
			p.softBodyPointNum = (softBodyPointNum);
			return p;
		}
		PosVec SoftBodyManager::getConstraintPos(int softBodyNum, int pointNum)
		{
			return softBodies[softBodyNum]->requestPositions(0, pointNum);
		}
	} /* namespace solver */
} /* namespace quarks */
