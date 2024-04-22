#include "OdeSolver.h"


namespace quarks::solver {
    static
    void observer(const state_type &x, const double t) {
    }

    static
    void system(const state_type &x, state_type &dxdt, double t) {
        dxdt[0] = x[3];
        dxdt[1] = x[4];
        dxdt[2] = x[5];
        dxdt[3] = x[6];
        dxdt[4] = x[7];
        dxdt[5] = x[8];
        dxdt[6] = 0;
        dxdt[7] = 0;
        dxdt[8] = 0;
    }

    void OdeSolver::ApplyRK4(const Scalar time_step, const PosVec &old_pos, const DirVec &old_vel,
                             const DirVec &old_acc, PosVec &new_pos, DirVec &new_vel) {
        state_type state;
        state[0] = old_pos.x();
        state[1] = old_pos.y();
        state[2] = old_pos.z();
        state[3] = old_vel.x();
        state[4] = old_vel.y();
        state[5] = old_vel.z();
        state[6] = old_acc.x();
        state[7] = old_acc.y();
        state[8] = old_acc.z();
        boost::numeric::odeint::integrate(system, state, 0.0, time_step, time_step, observer);
        new_pos.assign(state[0], state[1], state[2]);
        new_vel.assign(state[3], state[4], state[5]);
    }

    void OdeSolver::ApplyEuler(const Scalar time_step, const PosVec &old_pos, const DirVec &old_vel,
                               const DirVec &old_acc, PosVec &new_pos, DirVec &new_vel) {
        new_vel = old_vel + old_acc * time_step;
        new_pos = old_pos + new_vel * time_step;
    }
} // namespace quarks::solver
