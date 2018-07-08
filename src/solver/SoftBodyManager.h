/*
 * SoftBodyManager.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef SOFTBODYMANAGER_H_
#define SOFTBODYMANAGER_H_
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include "../base_types/Particle.h"
#include "../base_types/Spring.h"
#include "../sources/Source.h"
#include "../sources/SoftBodySource.h"
#include <map>
namespace quarks
{
	namespace solver
	{

		class SoftBodyManager
		{
		public:
			SoftBodyManager()
			{
				softBodies.clear();
				maxID = 0;
			}
			virtual ~SoftBodyManager(){};
			void birthParticles(std::vector<Particle> & particles, std::vector<Spring> & springs,
					unsigned int time);
			inline void addSoftBody(quarks::sources::SoftBodySourcePtr f)
			{
				softBodies.push_back(f);
			}
			inline void clearSoftBodies()
			{
				softBodies.clear();
			}
			inline PosVec getConstraintPos(int softBodyNum, int pointNum)
			{
				return softBodies[softBodyNum]->requestPositions(0, pointNum);
			}
		private:
			std::vector<quarks::sources::SoftBodySourcePtr> softBodies;
			unsigned int maxID;
			std::map<int, std::vector<Particle*> > srcMap;
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* SOURCEMANAGER_H_ */
