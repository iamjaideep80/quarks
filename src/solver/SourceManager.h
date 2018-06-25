/*
 * SourceManager.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef SOURCEMANAGER_H_
#define SOURCEMANAGER_H_
#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include "../base_types/Particle.h"
#include "../base_types/Spring.h"
#include "../sources/Source.h"
#include<map>
namespace quarks
{
	namespace solver
	{

		class SourceManager
		{
		public:
			SourceManager();
			virtual ~SourceManager();
			void birthParticles(std::vector<Particle> & particles, unsigned int time);
			void addSource(quarks::sources::SourcePtr f);
			void clearSources();
		private:
			std::vector<quarks::sources::SourcePtr> sources;
			unsigned int maxID;
		};

	} /* namespace solver */
} /* namespace quarks */
#endif /* SOURCEMANAGER_H_ */
