#include <UT/UT_DSOVersion.h>
#include <GU/GU_Detail.h>
#include <OP/OP_Director.h>
#include <OP/OP_Operator.h>
#include <OP/OP_OperatorTable.h>
#include "SOP_Quarks.h"

void newSopOperator(OP_OperatorTable *table) {
    table->addOperator(
        new OP_Operator("quarks", "Quarks", SOP_Quarks::myConstructor, SOP_Quarks::template_list, 1,
                        // Min required sources
                        4, // Maximum sources
                        0));
}

// The names here have to match the inline evaluation functions
static PRM_Name names[] =
{
    PRM_Name("reset", "Reset Frame"), PRM_Name("subSteps", "Sub Steps"), PRM_Name("sim_time_scale",
        "Simulation Time Scale"),
};

static PRM_Default defaultSubSteps(1);

PRM_Template SOP_Quarks::template_list[] =
{
    PRM_Template(PRM_INT, 1, &names[0], PRMoneDefaults), PRM_Template(PRM_INT_J, 1, &names[1],
                                                                      &defaultSubSteps),
    PRM_Template(PRM_FLT, 1, &names[2], PRMoneDefaults), PRM_Template(),
};

OP_Node *
SOP_Quarks::myConstructor(OP_Network *net, const char *name, OP_Operator *op) {
    return new SOP_Quarks(net, name, op);
}

SOP_Quarks::SOP_Quarks(OP_Network *net, const char *name, OP_Operator *op) : SOP_Node(net, name, op) {
    last_cook_time_ = 0;
}

void SOP_Quarks::InitializeSystem() {
    adapter_.SetGdp(gdp);
    adapter_.InitializeSystem();
    if (inputGeo(static_cast<int>(InputIndex::COLLISION))) {
        adapter_.SetCollisions(inputGeo(static_cast<int>(InputIndex::COLLISION)));
    }
}

OP_ERROR SOP_Quarks::cookMySop(OP_Context &context) {
    if (lockInputs(context) >= UT_ERROR_ABORT)
        return error();
    OP_Node::flags().setTimeDep(true);
    const CH_Manager *ch_manager = OPgetDirector()->getChannelManager();
    fpreal curr_frame = ch_manager->getSample(context.getTime());

    if (curr_frame <= RESET()) {
        gdp->clearAndDestroy();
        last_cook_time_ = RESET();
        InitializeSystem();
    }

    curr_frame += 0.05; // Add a bit to avoid floating point error
    while (last_cook_time_ < curr_frame) {
        const fpreal now = ch_manager->getTime(last_cook_time_);
        if (inputGeo(static_cast<int>(InputIndex::SOURCE)))
            adapter_.SetSources(inputGeo(static_cast<int>(InputIndex::SOURCE)));
        if (inputGeo(static_cast<int>(InputIndex::FORCE)))
            adapter_.SetForces(inputGeo(static_cast<int>(InputIndex::FORCE)));
        if (inputGeo(static_cast<int>(InputIndex::SOFTBODY)))
            adapter_.SetSoftBodies(inputGeo(static_cast<int>(InputIndex::SOFTBODY)));
        const fpreal fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();
        adapter_.StepForward(fps / SIM_TIME_SCALE(), SUBSTEPS(now));
        last_cook_time_ += 1;
    }

    const fpreal fps = OPgetDirector()->getChannelManager()->getSamplesPerSec();
    adapter_.SyncHoudini(fps / SIM_TIME_SCALE());
    unlockInputs();
    return error();
}

const char *
SOP_Quarks::inputLabel(unsigned idx) const {
    switch (static_cast<InputIndex>(idx)) {
        case InputIndex::SOURCE:
            return "Particle Source Geometry";
        case InputIndex::FORCE:
            return "Forces";
        case InputIndex::COLLISION:
            return "Collisions";
        case InputIndex::SOFTBODY:
            return "Soft Body Source";
        default:
            return "Unknown source";
    }
}
