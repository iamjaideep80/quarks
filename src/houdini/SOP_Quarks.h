#ifndef SOP_Quarks_h_
#define SOP_Quarks_h_

#include "HQAdapter.h"
#include <SOP/SOP_Node.h>

class SOP_Quarks : public SOP_Node {
public:
    SOP_Quarks(OP_Network *net, const char *name, OP_Operator *op);

    ~SOP_Quarks() override = default;

    static PRM_Template myTemplateList[];

    static OP_Node *myConstructor(OP_Network *, const char *, OP_Operator *);

protected:
    const char *inputLabel(unsigned idx) const override;

    void InitializeSystem();

    OP_ERROR cookMySop(OP_Context &context) override;

private:
    enum class InputIndex {
        SOURCE,
        FORCE,
        COLLISION,
        SOFTBODY
    };

    int RESET() const {
        return evalInt("reset", 0, 0);
    }

    int SUBSTEPS(const fpreal t) const {
        return evalInt("subSteps", 0, t);
    }

    fpreal SIM_TIME_SCALE() const {
        return evalFloat("sim_time_scale", 0, 0);
    }

    fpreal myLastCookTime; // Last cooked time
    static int *myOffsets;
    quarks::houdini::HQAdapter adapter;
};

#endif
