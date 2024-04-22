#ifndef NOISEFORCE_H_
#define NOISEFORCE_H_
#include "Force.h"

namespace quarks::forces {
    class Noise_Force : public Force {
    public:
        explicit Noise_Force(const Scalar amp) {
            amplitude_ = amp;
        };

        ~Noise_Force() override = default;

        DirVec CalculateForce(PosVec pos, DirVec vel) const override;

    private:
        Scalar amplitude_;
    };
} // namespace quarks::forces

#endif /* NOISEFORCE_H_ */
