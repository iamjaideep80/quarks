/*
 * ForceManager.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef FORCEMANAGER_H_
#define FORCEMANAGER_H_
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include "../base_types/Particle.h"
#include "../base_types/Spring.h"
#include "../forces/Force.h"
namespace quarks
{
	namespace solver
	{

		class ForceManager
		{
		public:
			ForceManager();
			virtual ~ForceManager();
			void addForce(quarks::forces::Force* f);
			void clearForces();
			void accumulateForces(std::vector<Particle> & particles, const std::vector<Spring*> & springs);
		private:
			void accumulateExternalForces(std::vector<Particle> & particles);
			void accumulateInternalForces(const std::vector<Spring*> & springs);
			std::vector<quarks::forces::Force*> forces;
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* FORCEMANAGER_H_ */
