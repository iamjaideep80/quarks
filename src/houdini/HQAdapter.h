/*
 * HoudiniQuarksAdaptor.h
 *
 *  Created on: 22-Feb-2014
 *      Author: jaideep
 */
#ifndef HOUDINIQUARKSADAPTER_H_
#define HOUDINIQUARKSADAPTER_H_
#include "../solver/ParticleSystem.h"
#include "GEO/GEO_PrimPart.h"
#include "GU/GU_Detail.h"
#include "GU/GU_PrimVDB.h"
namespace quarks
{
	namespace houdini
	{
		class HQAdapter
		{
		public:
			HQAdapter();
			virtual ~HQAdapter();
			void initializeSystem();
			void setSources(const GU_Detail* source);
			void setSoftBodies(const GU_Detail* source);
			void setForces(const GU_Detail* force);
			void setCollisions(const GU_Detail* collision);
			void stepForward(GU_Detail* gdp, fpreal fps, int subSteps);
			void syncHoudini(fpreal fps);
			void setGdp(GU_Detail* gdpInput);

		private:
			quarks::solver::ParticleSystem quarks;
			GEO_PrimParticle* particlePrimPtr;
			GU_Detail* gdp;
			GA_RWAttributeRef idRef;
			GA_RWAttributeRef lifeRef;
			GA_RWAttributeRef velRef;
		};
	} /* namespace houdini */
} /* namespace quarks */
#endif /* HOUDINIQUARKSADAPTOR_H_ */
