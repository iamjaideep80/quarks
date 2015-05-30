/*
 * OdeSolver.cpp
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#include "OdeSolver.h"

namespace quarks
{
	namespace solver
	{

		OdeSolver::OdeSolver()
		{
			// TODO Auto-generated constructor stub

		}

		OdeSolver::~OdeSolver()
		{
			// TODO Auto-generated destructor stub
		}
		static
		void observer(const state_type& x, const double t)
		{
		}
		static
		void differential(const state_type& x, state_type& dxdt, double t)
		{
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
		void OdeSolver::applyRK4(const Scalar timeStep, const PosVec& oldPos, const DirVec& oldVel,
				const DirVec& oldForce, PosVec& newPos, DirVec& newVel)
		{
			state_type state;
			state[0] = oldPos.x();
			state[1] = oldPos.y();
			state[2] = oldPos.z();
			state[3] = oldVel.x();
			state[4] = oldVel.y();
			state[5] = oldVel.z();
			state[6] = oldForce.x();
			state[7] = oldForce.y();
			state[8] = oldForce.z();
			boost::numeric::odeint::integrate(differential, state, 0.0, timeStep, timeStep, observer);
			newPos.assign(state[0], state[1], state[2]);
			newVel.assign(state[3], state[4], state[5]);
		}
		void OdeSolver::applyEuler(const Scalar timeStep, const PosVec& oldPos, const DirVec& oldVel,
				const DirVec& oldForce, PosVec& newPos, DirVec& newVel)
		{
			newVel = oldVel + oldForce * timeStep;
			newPos = oldPos + newVel * timeStep;
		}
	} /* namespace solver */
} /* namespace quarks */
