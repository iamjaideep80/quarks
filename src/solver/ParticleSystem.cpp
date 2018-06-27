#include <boost/numeric/odeint.hpp>
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
#include <openvdb/math/Operators.h>
#include <openvdb/math/FiniteDifference.h>
#include "OdeSolver.h"
#include <thread>
#include <math.h>
#include "ParticleSystem.h"
#include <chrono>
typedef CGAL::Cartesian_d<double> Kd;
typedef Kd::Point_d Point;
namespace quarks
{
	namespace solver
	{
		ParticleSystem::ParticleSystem()
		{
			particles.reserve(MAX_NUM_PARTICLES);
			collision = NULL;
			IsCollisionRegistered = false;
			clothSolverFlag = false;
			initializeSystem();
		}
		void ParticleSystem::initializeSystem()
		{
			particles.clear();
			springs.clear();
			steps = 0;
		}
		bool ParticleSystem::isClothSolverFlag() const
		{
			return clothSolverFlag;
		}

		void ParticleSystem::setClothSolverFlag(bool clothSolverFlag)
		{
			this->clothSolverFlag = clothSolverFlag;
		}

		void ParticleSystem::stepForward(Scalar timeStep)
		{
//			std::cout << "-------------------------------------" << std::endl;
			auto start = std::chrono::steady_clock::now();
			sourceManager.birthParticles(particles, steps);
			auto checkpoint1 = std::chrono::steady_clock::now();
//			std::cout << std::chrono::duration <double, std::milli> (checkpoint1-start).count() << " ms" << std::endl;

			softBodyManager.birthParticles(particles, springs, steps);
			auto checkpoint2 = std::chrono::steady_clock::now();
//			std::cout << std::chrono::duration <double, std::milli> (checkpoint2-checkpoint1).count() << " ms" << std::endl;


			forceManager.accumulateInternalForces(springs);
			auto checkpoint3 = std::chrono::steady_clock::now();
//			std::cout << std::chrono::duration <double, std::milli> (checkpoint3-checkpoint2).count() << " ms" << std::endl;

			int numOfThreads = std::thread::hardware_concurrency() - 1;

			std::vector<std::thread> threadsA;
			for (unsigned i = 0; i < numOfThreads; i++)
				threadsA.push_back(std::thread(&ParticleSystem::solveStep, this, i, numOfThreads,timeStep));

			for (auto& thread : threadsA)
				thread.join();

			auto checkpoint4 = std::chrono::steady_clock::now();
//			std::cout << std::chrono::duration <double, std::milli> (checkpoint4-checkpoint3).count() << " ms" << std::endl;
			steps++;
		}

		void ParticleSystem::solveStep(int threadIndex, int numThreads, Scalar timeStep)
		{
			for (int i = threadIndex; i < particles.size(); i += numThreads)
			{
				Particle& particle = particles[i];
				if (particle.life > particle.lifeExpectancy)
				{
					continue;
				}

				forceManager.accumulateExternalForces(particle);

				PosVec oldPos = particle.position;
				DirVec oldVel = particle.velocity;
				DirVec oldForce = particle.force / particle.mass;
				PosVec newPos;
				DirVec newVel;
				OdeSolver odeSolver;

				if (particle.isFixed)
				{
					particle.position = softBodyManager.getConstraintPos(particle.softBodySourceNum,
																			particle.softBodyPointNum);
					continue;
				}

				if (clothSolverFlag)
					odeSolver.applyRK4(timeStep, oldPos, oldVel, oldForce, newPos, newVel);
				else
					odeSolver.applyEuler(timeStep, oldPos, oldVel, oldForce, newPos, newVel);

				if (IsCollisionRegistered)
					collision->applyCollision(oldPos, oldVel, newPos, newVel);

				particle.position = newPos;
				particle.velocity = newVel;
				particle.life++;
				particle.force = 0;
			}
		}
	}
} /* namespace quarks */
