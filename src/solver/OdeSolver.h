#ifndef ODESOLVER_H_
#define ODESOLVER_H_
#include "../base_types/CommonTypes.h"
#include <boost/numeric/odeint.hpp>

namespace quarks::solver {
    using state_type = boost::array<Scalar, 9>;

    class OdeSolver {
    public:
        OdeSolver() = default;

        ~OdeSolver() = default;

        static void ApplyRK4(const Scalar time_step, const PosVec &old_pos, const DirVec &old_vel,
                             const DirVec &old_acc, PosVec &new_pos, DirVec &new_vel);

        static void ApplyEuler(const Scalar time_step, const PosVec &old_pos, const DirVec &old_vel,
                               const DirVec &old_acc, PosVec &new_pos, DirVec &new_vel);
    };
} // namespace quarks::solver

#endif /* ODESOLVER_H_ */
