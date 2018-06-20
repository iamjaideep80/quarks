/*
 * SoftBodyData.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "SoftBodyData.h"

namespace quarks
{
	namespace sources
	{

		SoftBodyData::SoftBodyData(Scalar springConstant, Scalar dampingConstant, bool active) :
				springConstant(springConstant), dampingConstant(dampingConstant), active(active)
		{
		}

		SoftBodyData::~SoftBodyData()
		{
			// TODO Auto-generated destructor stub
		}

		Scalar SoftBodyData::getDampingConstant() const
		{
			return dampingConstant;
		}

		void SoftBodyData::setDampingConstant(Scalar dampingConstant)
		{
			this->dampingConstant = dampingConstant;
		}

		Scalar SoftBodyData::getSpringConstant() const
		{
			return springConstant;
		}

		void SoftBodyData::setSpringConstant(Scalar springConstant)
		{
			this->springConstant = springConstant;
		}
		void SoftBodyData::insertSpring(int indexA, int indexB)
		{
			springMap.insert(std::pair<int, int>(indexA, indexB));
		}
		void SoftBodyData::insertPoint(PosVec initPos, bool isFix)
		{
			this->initPosVec.push_back(initPos);
			this->fixVec.push_back(isFix);
		}

		const std::vector<PosVec>& SoftBodyData::getInitPosVec() const
		{
			return initPosVec;
		}

		const SpringMap& SoftBodyData::getSpringMap() const
		{
			return springMap;
		}

		const std::vector<bool>& SoftBodyData::getFixVec() const
		{
			return fixVec;
		}

		bool SoftBodyData::isActive() const
		{
			return active;
		}

		void SoftBodyData::setActive(bool active)
		{
			this->active = active;
		}

	} /* namespace sources */
} /* namespace quarks */
