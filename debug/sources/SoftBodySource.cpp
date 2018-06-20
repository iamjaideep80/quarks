/*
 * SoftBodySource.cpp
 *
 *  Created on: 09-Mar-2014
 *      Author: jaideep
 */
#include "SoftBodySource.h"
namespace quarks
{
	namespace sources
	{
		SoftBodySource::SoftBodySource(SoftBodyData softBodyData)
		{
			this->lifeExpectancy = INT_MAX;
			this->springConstant = softBodyData.getSpringConstant();
			this->dampingConstant = softBodyData.getDampingConstant();
			myType = SOFTBODY_SOURCE;
			initPosVec = softBodyData.getInitPosVec();
			fixVec = softBodyData.getFixVec();
			springMap = softBodyData.getSpringMap();
			birthRate = initPosVec.size();
			active = softBodyData.isActive();
		}
		SoftBodySource::~SoftBodySource()
		{
			// TODO Auto-generated destructor stub
		}
		std::vector<PosVec> SoftBodySource::requestPositions(unsigned int time)
		{
			return initPosVec;
		}

		PosVec SoftBodySource::requestPositions(unsigned int time,int pointNum)
		{
			return initPosVec[pointNum];
		}
		std::vector<bool> SoftBodySource::requestFixPoints(unsigned int time)
		{
			return fixVec;
		}

		void SoftBodySource::insertSpring(int indexA, int indexB)
		{
			springMap.insert(std::pair<int, int>(indexA, indexB));
		}

		SpringMap SoftBodySource::requestSpringMap(unsigned int time)
		{
			return springMap;
		}

		void SoftBodySource::insertPoint(PosVec initPos)
		{
			this->initPosVec.push_back(initPos);
			birthRate++;
		}

		Scalar SoftBodySource::getSpringConstant() const
		{
			return springConstant;
		}

		void SoftBodySource::setSpringConstant(Scalar springConstant)
		{
			this->springConstant = springConstant;
		}

		Scalar SoftBodySource::getDampingConstant() const
		{
			return dampingConstant;
		}

		void SoftBodySource::setDampingConstant(Scalar dampingConstant)
		{
			this->dampingConstant = dampingConstant;
		}

		bool SoftBodySource::isActive() const
		{
			return active;
		}

		void SoftBodySource::setActive(bool active)
		{
			this->active = active;
		}

	} /* namespace sources */
} /* namespace quarks */
