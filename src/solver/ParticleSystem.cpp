#include <boost/numeric/odeint.hpp>
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
#include <openvdb/math/Operators.h>
#include <openvdb/math/FiniteDifference.h>
#include "OdeSolver.h"
#include <thread>
#include <math.h>
#include "ParticleSystem.h"
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
			for (int i = 0; i < springs.size(); i++)
			{
				delete springs[i];
			}
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
			sourceManager.birthParticles(particles, steps);
			softBodyManager.birthParticles(particles, springs, steps);
			forceManager.accumulateForces(particles, springs);
			theadedOperation(timeStep);
			steps++;
		}

		void ParticleSystem::theadedOperation(Scalar timeStep)
		{
			int numOfThreads = std::thread::hardware_concurrency() - 1;

			std::vector<std::thread> threadsA;
			for (unsigned i = 0; i < numOfThreads; i++)
			{
				threadsA.push_back(
						std::thread(&ParticleSystem::solveStep, this, i, numOfThreads,
									timeStep));
			}
			for (auto& thread : threadsA)
			{
				thread.join();
			}

			std::vector<std::thread> threadsB;
			for (unsigned i = 0; i < numOfThreads; i++)
			{
				threadsB.push_back(
						std::thread(&ParticleSystem::killOldParticles, this, i, numOfThreads));
			}
			for (auto& thread : threadsB)
			{
				thread.join();
			}
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
				PosVec oldPos = particle.position;
				DirVec oldVel = particle.velocity;
				DirVec oldForce = particle.force / particle.mass;
				PosVec newPos;
				DirVec newVel;
				OdeSolver odeSolver;

				if (particle.isFixed)
				{
					PosVec constraintPos = softBodyManager.getConstraintPos(particle.softBodySourceNum,
																			particle.softBodyPointNum);
					particle.position = constraintPos;
					continue;
				}

				if (clothSolverFlag)
					odeSolver.applyRK4(timeStep, oldPos, oldVel, oldForce, newPos, newVel);
				else
					odeSolver.applyEuler(timeStep, oldPos, oldVel, oldForce, newPos, newVel);

				if (IsCollisionRegistered)
				{
					collision->applyCollision(oldPos, oldVel, newPos, newVel);
				}
				particle.position = (newPos);
				particle.velocity = (newVel);
				particle.life = (particle.life + 1);
			}
		}

		void ParticleSystem::killOldParticles(int threadIndex, int numThreads)
		{
//			for (int i = threadIndex; i < particles.size(); i += numThreads)
//			{
//				Particle& particle = particles[i];
//				if (particle.life > particle.lifeExpectancy)
//				{
//					continue;
//				}
//			}
		}
	}
} /* namespace quarks */
