/*
 * OdeSolver.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef ODESOLVER_H_
#define ODESOLVER_H_
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include <boost/numeric/odeint.hpp>
namespace quarks
{
	namespace solver
	{
		typedef boost::array<Scalar, 9> state_type;
		class OdeSolver
		{
		public:
			OdeSolver();
			virtual ~OdeSolver();
			void applyRK4(const Scalar timeStep, const PosVec& oldPos, const DirVec& oldVel,
					const DirVec& oldForce, PosVec& newPos, DirVec& newVel);
			void applyEuler(const Scalar timeStep, const PosVec& oldPos, const DirVec& oldVel,
								const DirVec& oldForce, PosVec& newPos, DirVec& newVel);
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* ODESOLVER_H_ */
