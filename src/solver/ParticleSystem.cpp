#include "ParticleSystem.h"
#include <boost/numeric/odeint.hpp>
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
#include <openvdb/math/Operators.h>
#include <openvdb/math/FiniteDifference.h>
#include "OdeSolver.h"
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
			initializeSystem();
		}
		void ParticleSystem::initializeSystem()
		{
			for (int i = 0; i < particles.size(); i++)
			{
				delete particles[i];
			}
			particles.clear();
			springs.clear();
			steps = 0;
		}
		void ParticleSystem::stepForward(Scalar timeStep)
		{
			sourceManager.birthParticles(particles, steps);
			softBodyManager.birthParticles(particles, springs, steps);
			forceManager.accumulateForces(particles, springs);
			solveStep(timeStep);
			killOldParticles();
			steps++;
		}
		void ParticleSystem::solveStep(Scalar timeStep)
		{
			for (int i = 0; i < particles.size(); i++)
			{
				Particle* partPtr = particles[i];
				if (partPtr == NULL)
				{
					continue;
				}
				PosVec oldPos = partPtr->getPosition();
				DirVec oldVel = partPtr->getVelocity();
				DirVec oldForce = partPtr->getForce() / partPtr->getMass();
				PosVec newPos;
				DirVec newVel;
				OdeSolver odeSolver;

				if (partPtr->isIsFixed())
				{
					PosVec constraintPos = softBodyManager.getConstraintPos(partPtr->getSoftBodySourceNum(),
																			partPtr->getSoftBodyPointNum());
					partPtr->setPosition(constraintPos);
					continue;
				}

				odeSolver.applyOde(timeStep, oldPos, oldVel, oldForce, newPos, newVel);
				if (IsCollisionRegistered)
				{
					collision->applyCollision(oldPos, oldVel, newPos, newVel);
				}
				partPtr->setPosition(newPos);
				partPtr->setVelocity(newVel);
				partPtr->setLife(partPtr->getLife() + 1);
			}
		}
		void ParticleSystem::killOldParticles()
		{
			for (int i = 0; i < particles.size(); i++)
			{
				if (particles[i] == NULL)
				{
//					break;
					continue;
				}
				if (particles[i]->getLife() > particles[i]->getLifeExpectany())
				{
					delete particles[i];
					particles[i] = NULL;
//					particles.erase(particles.begin() + i);
				}
			}
		}
	}
} /* namespace quarks */
