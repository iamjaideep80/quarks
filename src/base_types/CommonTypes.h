#ifndef COMMONTYPES_H_
#define COMMONTYPES_H_
#include "UT/UT_Vector3.h"
#include<map>

namespace quarks {
    using PosVec = ::UT_Vector3R;
    using DirVec = ::UT_Vector3R;
    using Scalar = fpreal;
    using SpringMap = std::multimap<int, int>;
}
#endif /* COMMONTYPES_H_ */
