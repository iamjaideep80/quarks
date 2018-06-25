/*
 * Force.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef FORCE_H_
#define FORCE_H_
#include "../base_types/CommonTypes.h"
#include <memory>
using namespace quarks::base_types;
namespace quarks
{
	namespace forces
	{
		class Force
		{
		public:
			Force();
			virtual ~Force();
			virtual DirVec calculateFoce(PosVec pos, DirVec vel) = 0;
		};
		using ForcePtr = std::shared_ptr<Force>;
	}
} /* namespace quarks */
#endif /* FORCE_H_ */
