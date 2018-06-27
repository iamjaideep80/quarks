/*
 * Source.h
 *
 *  Created on: 02-Mar-2014
 *      Author: jaideep
 */
#ifndef SOURCE_H_
#define SOURCE_H_
#include <vector>
#include "SourceData.h"
#include "../base_types/CommonTypes.h"
#include <memory>
using quarks::base_types::PosVec;
using quarks::base_types::Scalar;
using quarks::base_types::DirVec;
using quarks::base_types::SpringMap;
namespace quarks
{
	namespace sources
	{
		class Source
		{
		public:
			Source()
			{
				birthRate = 10;
				lifeExpectancy = 10;
			};
			virtual ~Source(){};
			inline int getBirthRate() const
			{
				return birthRate;
			}
			inline void setBirthRate(int birthRate)
			{
				this->birthRate = birthRate;
			}
			inline Scalar getLifeExpectancy() const
			{
				return lifeExpectancy;
			}
			inline void setLifeExpectancy(Scalar lifeExpectancy)
			{
				this->lifeExpectancy = lifeExpectancy;
			}
			inline sourceType getMyType() const
			{
				return myType;
			}
			inline void setMyType(sourceType myType)
			{
				this->myType = myType;
			}
			virtual std::vector<PosVec> requestPositions(unsigned int time) = 0;

		protected:
			int birthRate;
			Scalar lifeExpectancy;
			sourceType myType;
		};
		using SourcePtr = std::shared_ptr<Source>;
	} /* namespace sources */
} /* namespace quarks */
#endif /* SOURCE_H_ */
