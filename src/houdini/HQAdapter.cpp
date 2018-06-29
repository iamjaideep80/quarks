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
		void HQAdapter::initializeSystem()
		{
			quarks.initializeSystem();
		}

		void HQAdapter::setSources(const GU_Detail* source)
		{
			quarks.clearSources();
			sources::SourceDataVector sourceDataVector;
			AttribManager attribManager;
			attribManager.extractSourceInfo(source, sourceDataVector);
			sources::SourceFactory sourceFactory;
			for(auto sourceData:sourceDataVector)
				quarks.addSource(sourceFactory.getSource(sourceData));
		}
		void HQAdapter::setSoftBodies(const GU_Detail* source)
		{
			quarks.clearSoftBodies();
			sources::SoftBodyDataVector softBodyDataVector;
			AttribManager attribManager;
			attribManager.extractSoftBodyInfo(source, softBodyDataVector);
			for (int i = 0; i < softBodyDataVector.size(); i++)
			{
				quarks.addSoftBody(sources::SoftBodySourcePtr(new sources::SoftBodySource(softBodyDataVector[i])));
			}
			quarks.setClothSolverFlag(true);
		}
		void HQAdapter::setForces(const GU_Detail* force)
		{
			quarks.clearForces();
			forces::ForceDataVector forceDataVec;
			AttribManager attribManager;
			attribManager.extractForceInfo(force, forceDataVec);
			forces::ForceFactory forceFactory;
			for (int i = 0; i < forceDataVec.size(); i++)
			{
				quarks.addForce(forceFactory.getForce(forceDataVec[i]));
			}
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
				const Particle& particle = quarks.getParticle(i);
				GA_Offset ptoff;
				if (particle.life > particle.lifeExpectancy)
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

				particlePrimPtr->getDetail().setPos3(ptoff, particle.position);
				UT_Vector2 life(particle.life / fps, particle.lifeExpectancy / fps);
				idRefTuple->set(idRef.getAttribute(), ptoff, &particle.id, 1);
				lifeRefTuple->set(lifeRef.getAttribute(), ptoff, life.data(), 2);
				velRefTuple->set(velRef.getAttribute(), ptoff, particle.velocity.data(), 3);
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
	} /* namespace houdini */
} /* namespace quarks */
