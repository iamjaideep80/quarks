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
			void stepForward(GU_Detail* gdp, fpreal fps,int subSteps);
			void syncHoudini(GU_Detail* gdp, fpreal fps);
		private:
			quarks::solver::ParticleSystem quarks;
			void addSources(const GU_Detail* source);
			void clearSources();
			void addSoftBodies(const GU_Detail* source);
			void clearSoftBodies();
			void addForces(const GU_Detail* force);
			void clearForces();
		};
	} /* namespace houdini */
} /* namespace quarks */
#endif /* HOUDINIQUARKSADAPTOR_H_ */
