#ifndef HOUDINIQUARKSADAPTER_H_
#define HOUDINIQUARKSADAPTER_H_
#include "../solver/ParticleSystem.h"
#include "GEO/GEO_PrimPart.h"
#include "GU/GU_Detail.h"


namespace quarks::houdini {
    class HQAdapter {
    public:
        HQAdapter(): particle_prim_ptr_(nullptr), gdp_(nullptr) {
        } ;

        ~HQAdapter() = default;

        void InitializeSystem();

        void SetSources(const GU_Detail *source);

        void SetSoftBodies(const GU_Detail *source);

        void SetForces(const GU_Detail *force);

        void SetCollisions(const GU_Detail *collision);

        void StepForward(fpreal fps, int sub_steps);

        void SyncHoudini(fpreal fps) const;

        void SetGdp(GU_Detail *gdpInput);

    private:
        solver::ParticleSystem quarks_;
        GEO_PrimParticle *particle_prim_ptr_;
        GU_Detail *gdp_;
        GA_RWAttributeRef id_ref_;
        GA_RWAttributeRef life_ref_;
        GA_RWAttributeRef vel_ref_;
    };
} // namespace quarks::houdini

#endif /* HOUDINIQUARKSADAPTER_H_ */
