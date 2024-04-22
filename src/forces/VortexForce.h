#ifndef VORTEXFORCE_H_
#define VORTEXFORCE_H_
#include "Force.h"

namespace quarks::forces {
    class Vortex_Force : public Force {
    public:
        Vortex_Force(const Scalar amp, const DirVec dir) : amplitude_(amp), direction_(dir) {
        }

        ~Vortex_Force() override = default;

        DirVec CalculateForce(const PosVec pos, const DirVec vel) const override {
            const DirVec modPos = pos - dot(direction_, pos) * direction_;
            return amplitude_ * cross(modPos, direction_);
        }

    private:
        Scalar amplitude_;
        DirVec direction_;
    };
} // namespace quarks::forces

#endif /* VORTEXFORCE_H_ */
