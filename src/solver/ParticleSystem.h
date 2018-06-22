#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_
#include <vector>
#include "../base_types/CommonTypes.h"
#include "../base_types/Particle.h"
#include "../collisions/Collision.h"
#include "../forces/Force.h"
#include "../sources/Source.h"
#include "../sources/SoftBodySource.h"
#include <boost/array.hpp>
#include "../base_types/Spring.h"
#include "SourceManager.h"
#include "SoftBodyManager.h"
#include "ForceManager.h"
namespace quarks
{
	namespace solver
	{
		const int MAX_NUM_PARTICLES = 10000000;
		class ParticleSystem
		{
		public:
			ParticleSystem();
			virtual ~ParticleSystem()
			{
				initializeSystem();
			}
			int getNumParticles()
			{
				return particles.size();
			}
			void initializeSystem();
			const Particle& getParticle(int index)
			{
				return particles[index];
			}
			void stepForward(Scalar timeStep);
			void addForce(quarks::forces::Force* f)
			{
				forceManager.addForce(f);
			}
			void clearForces()
			{
				forceManager.clearForces();
			}
			void addSource(quarks::sources::Source* f)
			{
				sourceManager.addSource(f);
			}
			void clearSources()
			{
				sourceManager.clearSources();
			}
			void addSoftBody(quarks::sources::SoftBodySource* f)
			{
				softBodyManager.addSoftBody(f);
			}
			void clearSoftBodies()
			{
				softBodyManager.clearSoftBodies();
			}
			void setCollision(collisions::Collision* coll)
			{
				collision = coll;
				IsCollisionRegistered = true;
			}

			bool isClothSolverFlag() const;
			void setClothSolverFlag(bool clothSolverFlag);

		private:
			std::vector<Particle> particles;
			std::vector<Spring*> springs;
			collisions::Collision* collision;
			bool IsCollisionRegistered;
			void theadedOperation(Scalar timeStep);
			void solveStep(int threadIndex, int numThreads, Scalar timeStep);
			void killOldParticles(int threadIndex, int numThreads);
			unsigned int steps;
			SourceManager sourceManager;
			ForceManager forceManager;
			SoftBodyManager softBodyManager;
			bool clothSolverFlag;
		};
	}
} /* namespace quarks */
#endif /* PARTICLESYSTEM_H_ */
