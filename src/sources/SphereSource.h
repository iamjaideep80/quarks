/*
 * SphereSource.h
 *
 *  Created on: 02-Mar-2014
 *      Author: jaideep
 */
#ifndef SPHERESOURCE_H_
#define SPHERESOURCE_H_
#include "Source.h"
namespace quarks
{
	namespace sources
	{
		class SphereSource : public quarks::sources::Source
		{
		public:
			SphereSource(Scalar rate, PosVec pos, Scalar size,Scalar lifeExpectancy);
			virtual ~SphereSource(){};
			std::vector<PosVec> requestPositions(unsigned int time);
		private:
			PosVec pos;
			Scalar size;
		};
	} /* namespace sources */
} /* namespace quarks */
#endif /* SPHERESOURCE_H_ */
