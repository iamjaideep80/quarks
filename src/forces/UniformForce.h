#ifndef UNIFORMFORCE_H_
#define UNIFORMFORCE_H_
#include "Force.h"

namespace quarks::forces {
    class Uniform_Force : public Force {
    public:
        Uniform_Force(const Scalar amp, const DirVec &dir): amplitude_(amp), direction_(dir) {
        }

        ~Uniform_Force() override = default;

        DirVec CalculateForce(PosVec pos, DirVec vel) const override {
            return amplitude_ * direction_;
        }

    private:
        Scalar amplitude_;
        DirVec direction_;
    };
} // namespace quarks::forces

#endif /* UNIFORMFORCE_H_ */
