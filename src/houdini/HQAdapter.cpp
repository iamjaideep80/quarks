/*
 * HoudiniQuarksAdapter.cpp
 *
 *  Created on: 22-Feb-2014
 *      Author: jaideep
 */
#include "HQAdapter.h"
#include "../forces/ForceFactory.h"
#include "../forces/ForceData.h"
#include "../sources/SourceFactory.h"
#include "../collisions/Collision.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include "../sources/SoftBodySource.h"
//#include "GU/GU_PrimPolySoup.h"
#include "AttribManager.h"
namespace quarks
{
	namespace houdini
	{
		HQAdapter::HQAdapter()
		{
			// TODO Auto-generated constructor stub
		}
		HQAdapter::~HQAdapter()
		{
			// TODO Auto-generated destructor stub
		}
		void HQAdapter::initializeSystem()
		{
			quarks.initializeSystem();
		}

		void HQAdapter::setSources(const GU_Detail* source)
		{
			clearSources();
			addSources(source);
		}
		void HQAdapter::setSoftBodies(const GU_Detail* source)
		{
			clearSoftBodies();
			addSoftBodies(source);
			quarks.setClothSolverFlag(true);
		}
		void HQAdapter::setForces(const GU_Detail* force)
		{
			clearForces();
			addForces(force);
		}
		void HQAdapter::setCollisions(const GU_Detail* collision)
		{
			collisions::CollisionDataVector collisionDataVec;
			AttribManager attribManager;
			attribManager.extractCollisionInfo(collision, collisionDataVec);
			for (int i = 0; i < collisionDataVec.size(); i++)
			{
				quarks.setCollision(new collisions::Collision(collisionDataVec[i]));
			}
		}
		void HQAdapter::stepForward(GU_Detail* gdp, fpreal fps, int subSteps)
		{
			for (int i = 0; i < subSteps; i++)
			{
				quarks.stepForward(1 / (fps * float(subSteps)));
			}
		}
		void HQAdapter::syncHoudini(fpreal fps)
		{
			const GA_AIFTuple* idRefTuple = idRef.getAIFTuple();
			const GA_AIFTuple* lifeRefTuple = lifeRef.getAIFTuple();
			const GA_AIFTuple* velRefTuple = velRef.getAIFTuple();
			int numParticles = quarks.getNumParticles();
			for (GA_Index i = 0; i < numParticles; i++)
			{
				Particle* particle = quarks.getParticle(i);
				GA_Offset ptoff;
				if (particle == NULL)
				{
					continue;
				}
				if (particlePrimPtr->getNumParticles() < (i + 1))
				{
					ptoff = particlePrimPtr->giveBirth();
				}
				else
				{
					ptoff = particlePrimPtr->getPointOffset(i);
				}

				UT_Vector3 pos = particle->getPosition();
				particlePrimPtr->getDetail().setPos3(ptoff, pos);
				UT_Vector2 life(particle->getLife() / fps, particle->getLifeExpectany() / fps);
				UT_Vector3 vel = particle->getVelocity();
				int64 idVal = particle->getId();
				idRefTuple->set(idRef.getAttribute(), ptoff, &idVal, 1);
				lifeRefTuple->set(lifeRef.getAttribute(), ptoff, life.data(), 2);
				velRefTuple->set(velRef.getAttribute(), ptoff, vel.data(), 3);
			}
		}

		void HQAdapter::addForces(const GU_Detail* force)
		{
			forces::ForceDataVector forceDataVec;
			AttribManager attribManager;
			attribManager.extractForceInfo(force, forceDataVec);
			forces::ForceFactory forceFactory;
			for (int i = 0; i < forceDataVec.size(); i++)
			{
				forces::Force* force = forceFactory.getForce(forceDataVec[i]);
				quarks.addForce(force);
			}
		}

		void HQAdapter::setGdp(GU_Detail* gdpInput)
		{
			gdp = gdpInput;
			particlePrimPtr = (GEO_PrimParticle*) (gdp->appendPrimitive(GEO_PRIMPART));
			idRef = gdp->addIntTuple(GA_ATTRIB_POINT, "id", 1);
			lifeRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "life", 2);
			velRef = gdp->addFloatTuple(GA_ATTRIB_POINT, "v", 3);
		}

		void HQAdapter::clearForces()
		{
			quarks.clearForces();
		}
		void HQAdapter::addSources(const GU_Detail* source)
		{
			sources::SourceDataVector sourceDataVector;
			AttribManager attribManager;
			attribManager.extractSourceInfo(source, sourceDataVector);
			sources::SourceFactory sourceFactory;
			for (int i = 0; i < sourceDataVector.size(); i++)
			{
				sources::Source* sourcePtr = sourceFactory.getSource(sourceDataVector[i]);
				quarks.addSource(sourcePtr);
			}
		}
		void HQAdapter::clearSources()
		{
			quarks.clearSources();
		}
		void HQAdapter::addSoftBodies(const GU_Detail* softBodyGDP)
		{
			sources::SoftBodyDataVector softBodyDataVector;
			AttribManager attribManager;
			attribManager.extractSoftBodyInfo(softBodyGDP, softBodyDataVector);
			for (int i = 0; i < softBodyDataVector.size(); i++)
			{
				sources::SoftBodySource* sbsPtr = new sources::SoftBodySource(softBodyDataVector[i]);
				quarks.addSoftBody(sbsPtr);
			}
		}
		void HQAdapter::clearSoftBodies()
		{
			quarks.clearSoftBodies();
		}

	} /* namespace houdini */
} /* namespace quarks */
