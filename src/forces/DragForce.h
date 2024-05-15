#ifndef DRAGFORCE_H_
#define DRAGFORCE_H_
#include "Force.h"

namespace quarks::forces {
    class Drag_Force : public Force {
    public:
        explicit Drag_Force(const Scalar amp) {
            amplitude = amp;
        }

        ~Drag_Force() override = default;

        DirVec CalculateForce(const PosVec pos, const DirVec vel) const override {
            return -1 * amplitude * vel;
        }

    private:
        Scalar amplitude;
    };
} // namespace quarks::forces

#endif /* DRAGFORCE_H_ */
