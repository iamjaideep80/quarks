/*
 * Source.cpp
 *
 *  Created on: 02-Mar-2014
 *      Author: jaideep
 */
#include "Source.h"
namespace quarks
{
	namespace sources
	{
		Source::Source()
		{
			birthRate = 10;
			lifeExpectancy = 10;
		}
		Source::~Source()
		{
			// TODO Auto-generated destructor stub
		}

		Scalar Source::getLifeExpectancy() const
		{
			return lifeExpectancy;
		}

		void Source::setLifeExpectancy(Scalar lifeExpectancy)
		{
			this->lifeExpectancy = lifeExpectancy;
		}

		sourceType Source::getMyType() const
		{
			return myType;
		}

		void Source::setMyType(sourceType myType)
		{
			this->myType = myType;
		}

	} /* namespace sources */
} /* namespace quarks */
