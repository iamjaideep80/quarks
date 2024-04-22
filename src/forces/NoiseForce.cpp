#include "NoiseForce.h"

namespace quarks::forces {
    DirVec Noise_Force::CalculateForce(const PosVec pos, const DirVec vel) const {
        DirVec old_vel = vel;
        old_vel.normalize();
        DirVec random_vel(SYSdrand48() - .5, SYSdrand48() - .5, SYSdrand48() - .5);
        random_vel.normalize();
        DirVec new_vel = 0.5 * old_vel + 0.5 * random_vel;
        new_vel.normalize();
        return amplitude_ * new_vel;
    }
} // namespace quarks::forces
