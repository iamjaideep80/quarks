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
			ForceManager(){};
			virtual ~ForceManager(){};
			inline void addForce(quarks::forces::ForcePtr f)
			{
				forces.push_back(f);
			};
			inline void clearForces()
			{
				forces.clear();
			}
			inline void accumulateExternalForces(Particle& particle)
			{
				for (int j = 0; j < forces.size(); j++)
					particle.force += forces[j]->calculateFoce(particle.position,particle.velocity);
			};
			void accumulateInternalForces(std::vector<Spring> & springs);
		private:
			std::vector<quarks::forces::ForcePtr> forces;
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* FORCEMANAGER_H_ */
