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
#include<map>
namespace quarks
{
	namespace solver
	{

		class SoftBodyManager
		{
		public:
			SoftBodyManager();
			virtual ~SoftBodyManager();
			void birthParticles(std::vector<Particle> & particles, std::vector<Spring> & springs,
					unsigned int time);
			void addSoftBody(quarks::sources::SoftBodySource* f);
			void clearSoftBodies();
			PosVec getConstraintPos(int softBodyNum, int pointNum);
		private:
			Particle birthSingleParticle(PosVec intPos, Scalar initLifeExpectancy, bool isFix,
					int softBodySourceNum, int softBodyPointNum);
			std::vector<quarks::sources::SoftBodySource*> softBodies;
			unsigned int maxID;
			std::map<int, std::vector<Particle*> > srcMap;
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* SOURCEMANAGER_H_ */
