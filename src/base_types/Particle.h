#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "CommonTypes.h"
namespace quarks {
namespace base_types {
struct Particle {
	Particle(PosVec in_position,Scalar in_lifeExpectancy, unsigned int in_id) :
			position(in_position),id(in_id), lifeExpectancy(in_lifeExpectancy) {};
	PosVec position{0.0};
	DirVec velocity{0.0};
	Scalar mass = 10;
	DirVec force{0.0};
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
