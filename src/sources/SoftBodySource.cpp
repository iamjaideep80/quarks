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
	} /* namespace sources */
} /* namespace quarks */
