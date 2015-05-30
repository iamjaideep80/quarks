/*
 * Spring.cpp
 *
 *  Created on: 15-Mar-2014
 *      Author: jaideep
 */

#include "Spring.h"

namespace quarks
{
	namespace base_types
	{

		Spring::Spring(Particle* nodeA, Particle* nodeB, Scalar restLength, Scalar springConstant,
				Scalar dampingConstant) :
				nodeA(nodeA), nodeB(nodeB), restLength(restLength), springConstant(springConstant),
						dampingConstant(dampingConstant)
		{
		}

		Spring::~Spring()
		{
			// TODO Auto-generated destructor stub
		}

		void Spring::calculateForce(DirVec& forceA, DirVec& forceB)
		{
			PosVec posA = nodeA->getPosition();
			PosVec posB = nodeB->getPosition();
			DirVec vecAB = posB - posA;
			Scalar intensity = -1 * springConstant * (restLength - vecAB.length());
			vecAB.normalize();
			DirVec springForceA = intensity * vecAB;
			DirVec velA = nodeA->getVelocity();
			DirVec velB = nodeB->getVelocity();
			DirVec velDiff = velA - velB;
			DirVec dampingForceA;
			if (1)
				dampingForceA = -1 * velDiff * dampingConstant;
			else
				dampingForceA = -1 * (velDiff.dot(vecAB) * vecAB) * dampingConstant;
			forceA = springForceA + dampingForceA;
			forceB = -forceA;
		}

		Particle* Spring::getNodeA() const
		{
			return nodeA;
		}

		void Spring::setNodeA(Particle* nodeA)
		{
			this->nodeA = nodeA;
		}

		Particle* Spring::getNodeB() const
		{
			return nodeB;
		}

		void Spring::setNodeB(Particle* nodeB)
		{
			this->nodeB = nodeB;
		}

		void Spring::setRestLength(Scalar restLength)
		{
			this->restLength = restLength;
		}

		Scalar Spring::getSpringConstant() const
		{
			return springConstant;
		}

		void Spring::setSpringConstant(Scalar springConstant)
		{
			this->springConstant = springConstant;
		}

		Scalar Spring::getDampingConstant() const
		{
			return dampingConstant;
		}

		void Spring::setDampingConstant(Scalar dampingConstant)
		{
			this->dampingConstant = dampingConstant;
		}

	}
/* namespace base_types */
} /* namespace quarks */
