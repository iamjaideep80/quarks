/*
 * Force.h
 *
 *  Created on: 24-Feb-2014
 *      Author: jaideep
 */
#ifndef FORCE_H_
#define FORCE_H_
#include "../base_types/CommonTypes.h"
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
	}
} /* namespace quarks */
#endif /* FORCE_H_ */
