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
		void SoftBodyManager::birthParticles(std::vector<Particle*> & particles,
				std::vector<Spring*> & springs, unsigned int time)
		{
//			cout << "birthParticles CALLED" << endl;
//			cout << "softBodies.size() : " << softBodies.size() << endl;
			for (int softBodyNum = 0; softBodyNum < softBodies.size(); softBodyNum++)
			{
//				cout << "softBodyNum : " << softBodyNum << endl;
				quarks::sources::SoftBodySource* srcPtr = softBodies[softBodyNum];
				if (!srcPtr->isActive())
					continue;
				std::vector<PosVec> positions = srcPtr->requestPositions(time);
				std::vector<bool> fixPoints = srcPtr->requestFixPoints(time);
				for (int i = 0; i < fixPoints.size(); i++)
				{
//					cout << "Point : " << i << "  fixPoints : " << fixPoints[i] << endl;
				}
				std::vector<Particle*> source_particles;
				for (int pointNum = 0; pointNum < srcPtr->getBirthRate(); pointNum++)
				{
					PosVec initPos(positions[pointNum][0], positions[pointNum][1], positions[pointNum][2]);
					DirVec initVel(0, 0, 0);
					Scalar initLifeExpectancy = srcPtr->getLifeExpectancy();
					Particle* part = birthSingleParticle(initPos, initVel, initLifeExpectancy,
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
					Particle* nodeA = source_particles[nodePair.first];
					Particle* nodeB = source_particles[nodePair.second];
					DirVec vecAB = nodeA->getPosition() - nodeB->getPosition();
					Spring* spring = new Spring(nodeA, nodeB, vecAB.length(), sbSrcPtr->getSpringConstant(),
												sbSrcPtr->getDampingConstant());
					springs.push_back(spring);
				}
			}
		}
		Particle* SoftBodyManager::birthSingleParticle(PosVec initPos, DirVec initVel,
				Scalar initLifeExpectancy, bool isFix, int softBodySourceNum, int softBodyPointNum)
		{
			Particle* p = new Particle(initLifeExpectancy, maxID);
			maxID++;
			p->setPosition(initPos);
			p->setVelocity(initVel);
			p->setIsFixed(isFix);
			p->setSoftBodySourceNum(softBodySourceNum);
			p->setSoftBodyPointNum(softBodyPointNum);
//			particles.push_back(p);
			return p;
		}
		PosVec SoftBodyManager::getConstraintPos(int softBodyNum, int pointNum)
		{
			return softBodies[softBodyNum]->requestPositions(0, pointNum);
		}
	} /* namespace solver */
} /* namespace quarks */
