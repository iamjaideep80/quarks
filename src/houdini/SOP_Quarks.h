#ifndef __SOP_SParticle_h__
#define __SOP_SParticle_h__
#include "HQAdapter.h"
#include <SOP/SOP_Node.h>
#define INT_PARM(name, idx, vidx, t)	\
	    return evalInt(name, &myOffsets[idx], vidx, t);
#define FLT_PARM(name, idx, vidx, t)	\
	    return evalFloat(name, &myOffsets[idx], vidx, t);
class GEO_ParticleVertex;
class GEO_PrimParticle;
class GU_RayIntersect;
namespace HDK_Sample
{
	class SOP_Quarks : public SOP_Node
	{
	public:
		SOP_Quarks(OP_Network *net, const char *name, OP_Operator *op);
		virtual ~SOP_Quarks();
		static PRM_Template myTemplateList[];
		static OP_Node *myConstructor(OP_Network*, const char *, OP_Operator *);
	protected:
		virtual const char *inputLabel(unsigned idx) const;
		void initSystem();
		void stepForward(fpreal now);
		virtual OP_ERROR cookMySop(OP_Context &context);
	private:
		int RESET()
		{
			INT_PARM("reset", 0, 0, 0)
		}
		int SUBSTEPS(fpreal t)
		{
			INT_PARM("subSteps", 2, 0, t)
		}
		float SIM_TIME_SCALE()
		{
//		FLT_PARM("sim_time_scale", 0, 0, 0)
			return evalFloat("sim_time_scale", 0, 0);
		}
//    GEO_PrimParticle	*particlePrimPtr;
		fpreal myLastCookTime;	// Last cooked time
		static int *myOffsets;
		quarks::houdini::HQAdapter adapter;
		const GU_Detail* sourceGDP;
		const GU_Detail* forceGDP;
		const GU_Detail* collisionGDP;
		const GU_Detail* softBodyGDP;
	};
} // End HDK_Sample namespace
#endif
