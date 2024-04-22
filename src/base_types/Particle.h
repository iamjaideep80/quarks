#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "CommonTypes.h"

namespace quarks {
    struct Particle {
        Particle(const PosVec &in_position,
                 const Scalar in_lifeExpectancy,
                 const unsigned int in_id,
                 const bool in_is_fixed = false,
                 const unsigned int in_soft_body_source_num = 0,
                 const unsigned int in_soft_body_point_num = 0,
                 const Scalar in_mass = 10.0) : position(in_position),
                                                velocity{0, 0, 0},
                                                mass(in_mass),
                                                force{0, 0, 0},
                                                life(0),
                                                life_expectancy(in_lifeExpectancy),
                                                id(in_id),
                                                is_fixed(in_is_fixed),
                                                soft_body_source_num(in_soft_body_source_num),
                                                soft_body_point_num(in_soft_body_point_num) {
        };

        PosVec position;
        DirVec velocity;
        Scalar mass;
        DirVec force;
        Scalar life;
        Scalar life_expectancy;
        int64 id;
        bool is_fixed;
        unsigned int soft_body_source_num;
        unsigned int soft_body_point_num;
    };
} // namespace quarks

#endif /* PARTICLE_H_ */
