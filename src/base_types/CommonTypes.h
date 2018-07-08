/*
 * CommonTypes.h
 *
 *  Created on: 22-Feb-2014
 *      Author: jaideep
 */
#ifndef COMMONTYPES_H_
#define COMMONTYPES_H_
#include "UT/UT_Vector3.h"
#include<map>
namespace quarks
{
	namespace base_types
	{
		typedef ::UT_Vector3 PosVec;
		typedef ::UT_Vector3 DirVec;
		typedef fpreal Scalar;
		typedef std::multimap<int, int> SpringMap;
	}
}
#endif /* COMMONTYPES_H_ */
