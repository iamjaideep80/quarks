#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "CommonTypes.h"
namespace quarks {
namespace base_types {
struct Particle {
	Particle(PosVec in_position,
			Scalar in_lifeExpectancy,
			unsigned int in_id,
			bool in_isFixed=0,
			int in_softBodySourceNum=-1,
			int in_softBodyPointNum=-1) :
			position(in_position),
			id(in_id),
			lifeExpectancy(in_lifeExpectancy),
			isFixed(in_isFixed),
			softBodySourceNum(in_softBodySourceNum),
			softBodyPointNum(in_softBodyPointNum)
			{};
	PosVec position { 0.0 };
	DirVec velocity { 0.0 };
	Scalar mass = 10;
	DirVec force { 0.0 };
	Scalar life = 0;
	Scalar lifeExpectancy = 0;
	int64 id = 0;
	bool isFixed = 0;
	int softBodySourceNum = -1;
	int softBodyPointNum = -1;
};
}
}
#endif /* PARTICLE_H_ */
