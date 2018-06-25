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
			Source();
			virtual ~Source();
			int getBirthRate() const
			{
				return birthRate;
			}
			void setBirthRate(int birthRate)
			{
				this->birthRate = birthRate;
			}
			virtual std::vector<PosVec> requestPositions(unsigned int time) = 0;
			Scalar getLifeExpectancy() const;
			void setLifeExpectancy(Scalar lifeExpectancy);
			sourceType getMyType() const;
			void setMyType(sourceType myType);

		protected:
			int birthRate;
			Scalar lifeExpectancy;
			sourceType myType;
		};
		using SourcePtr = std::shared_ptr<Source>;
	} /* namespace sources */
} /* namespace quarks */
#endif /* SOURCE_H_ */
