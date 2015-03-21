#include <UT/UT_DSOVersion.h>
#include <UT/UT_Interrupt.h>
#include <UT/UT_Vector3.h>
#include <UT/UT_Vector4.h>
#include <GEO/GEO_PrimPart.h>
#include <GU/GU_Detail.h>
#include <GU/GU_RayIntersect.h>
#include <PRM/PRM_Include.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <GU/GU_PrimVDB.h>
#include <UT/UT_VDBUtils.h>
#include "SOP_Quarks.h"
#include <iostream>
#include "../base_types/Particle.h"
#include <boost/timer/timer.hpp>

using namespace HDK_Sample;
void newSopOperator(OP_OperatorTable *table)
{
	table->addOperator(
			new OP_Operator("quarks", "Quarks", SOP_Quarks::myConstructor, SOP_Quarks::myTemplateList, 1, // Min required sources
							4,	// Maximum sources
							0));
}
// The names here have to match the inline evaluation functions
static PRM_Name names[] =
{ PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name("sim_time_scale",
																				"Simulation Time Scale"), };
static PRM_Default defaultSubSteps(1);
PRM_Template SOP_Quarks::myTemplateList[] =
{ PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J, 1, &names[1],
																	&defaultSubSteps),
	PRM_Template(PRM_FLT, 1, &names[2], PRMoneDefaults), PRM_Template(), };
int * SOP_Quarks::myOffsets = 0;
OP_Node *
SOP_Quarks::myConstructor(OP_Network *net, const char *name, OP_Operator *op)
{
	return new SOP_Quarks(net, name, op);
}
SOP_Quarks::SOP_Quarks(OP_Network *net, const char *name, OP_Operator *op) :
		SOP_Node(net, name, op)
{
	// Make sure that our offsets are allocated.  Here we allow up to 32
	// parameters, no harm in over allocating.  The definition for this
	// function is in OP/OP_Parameters.h
	if (!myOffsets)
		myOffsets = allocIndirect(32);
	// Now, flag that nothing has been built yet...
	sourceGDP = NULL;
	forceGDP = NULL;
	collisionGDP = NULL;
	softBodyGDP = NULL;
	myLastCookTime = 0;
}
SOP_Quarks::~SOP_Quarks()
{
}
void SOP_Quarks::initSystem()
{
	adapter.initializeSystem();
	if (collisionGDP)
	{
		adapter.setCollisions(collisionGDP);
	}
}
void SOP_Quarks::stepForward(fpreal now)
{
	if (error() >= UT_ERROR_ABORT)
		return;
	if (sourceGDP)
	{
		adapter.setSources(sourceGDP);
	}
	if (forceGDP)
	{
		adapter.setForces(forceGDP);
	}
	if (softBodyGDP)
	{
		adapter.setSoftBodies(softBodyGDP);
	}
	fpreal fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();
	adapter.stepForward(gdp, fps / SIM_TIME_SCALE(), SUBSTEPS(now));
}
OP_ERROR SOP_Quarks::cookMySop(OP_Context &context)
{
//	boost::timer::auto_cpu_timer t;
	fpreal reset, currframe;
	CH_Manager *chman;
	gdp->clearAndDestroy();
	if (lockInputs(context) >= UT_ERROR_ABORT)
		return error();
	OP_Node::flags().timeDep = 1;
	sourceGDP = inputGeo(0);
	forceGDP = inputGeo(1);
	collisionGDP = inputGeo(2);
	softBodyGDP = inputGeo(3);
	chman = OPgetDirector()->getChannelManager();
	currframe = chman->getSample(context.getTime());
	reset = RESET();
	if (currframe <= reset)
	{
		myLastCookTime = reset;
		initSystem();
	}
	currframe += 0.05;	// Add a bit to avoid floating point error
	while (myLastCookTime < currframe)
	{
		stepForward(chman->getTime(myLastCookTime));
		myLastCookTime += 1;
	}
	fpreal fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();
	adapter.syncHoudini(gdp, fps / SIM_TIME_SCALE());
	unlockInputs();
	return error();
}
const char *
SOP_Quarks::inputLabel(unsigned inum) const
{
	switch (inum)
	{
	case 0:
		return "Particle Source Geometry";
	case 1:
		return "Forces";
	case 2:
		return "Collisions";
	case 3:
		return "Soft Body Source";
	}
	return "Unknown source";
}
