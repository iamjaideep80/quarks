#include "HQAdapter.h"

#include <memory>
#include "../forces/ForceFactory.h"
#include "../forces/ForceData.h"
#include "../sources/SourceFactory.h"
#include "../collisions/Collision.h"
#include "GU/GU_PrimVDB.h"
#include "../sources/SoftBodySource.h"
#include "AttribManager.h"


namespace quarks::houdini {
    void HQAdapter::InitializeSystem() {
        quarks_.InitializeSystem();
    }

    void HQAdapter::SetSources(const GU_Detail *source) {
        quarks_.ClearSources();
        sources::SourceDataVector source_data_vec;
        AttribManager::ExtractSourceInfo(source, source_data_vec);
        for (const auto &source_data: source_data_vec)
            quarks_.AddSource(sources::SourceFactory::GetSource(source_data));
    }

    void HQAdapter::SetSoftBodies(const GU_Detail *source) {
        quarks_.ClearSoftBodies();
        sources::SoftBodyDataVector soft_body_data_vec;
        AttribManager::ExtractSoftBodyInfo(source, soft_body_data_vec);
        for (const auto &soft_body_data: soft_body_data_vec) {
            quarks_.AddSoftBody(std::make_shared<sources::SoftBodySource>(soft_body_data));
        }
        quarks_.SetClothSolverFlag(true);
    }

    void HQAdapter::SetForces(const GU_Detail *force) {
        quarks_.ClearForces();
        forces::ForceDataVector force_data_vec;
        AttribManager::ExtractForceInfo(force, force_data_vec);
        for (const auto &force_data: force_data_vec) {
            if (const auto force_ptr = forces::ForceFactory::GetForce(force_data))
                quarks_.AddForce(force_ptr);
        }
    }

    void HQAdapter::SetCollisions(const GU_Detail *collision) {
        collisions::CollisionDataVector collision_data_vec;
        AttribManager::ExtractCollisionInfo(collision, collision_data_vec);
        for (const auto &collision_data: collision_data_vec) {
            quarks_.SetCollision(new collisions::Collision(collision_data));
        }
    }

    void HQAdapter::StepForward(const fpreal fps, const int sub_steps) {
        for (int i = 0; i < sub_steps; i++) {
            quarks_.StepForward(static_cast<fpreal>(1) / (fps * sub_steps));
        }
    }

    void HQAdapter::SyncHoudini(const fpreal fps) const {
        const GA_AIFTuple *id_ref_tuple = id_ref_.getAIFTuple();
        const GA_AIFTuple *life_ref_tuple = life_ref_.getAIFTuple();
        const GA_AIFTuple *vel_ref_tuple = vel_ref_.getAIFTuple();
        const auto num_particles = quarks_.GetNumParticles();
        for (GA_Index i = 0; i < num_particles; i++) {
            const Particle &particle = quarks_.GetParticle(i);
            GA_Offset ptoff;
            if (particle.life > particle.life_expectancy) {
                continue;
            }
            if (particle_prim_ptr_->getNumParticles() < (i + 1)) {
                ptoff = particle_prim_ptr_->giveBirth();
            } else {
                ptoff = particle_prim_ptr_->getPointOffset(i);
            }

            particle_prim_ptr_->getDetail().setPos3(ptoff, particle.position);
            UT_Vector2R life(particle.life / fps, particle.life_expectancy / fps);
            id_ref_tuple->set(id_ref_.getAttribute(), ptoff, &particle.id, 1);
            life_ref_tuple->set(life_ref_.getAttribute(), ptoff, life.data(), 2);
            vel_ref_tuple->set(vel_ref_.getAttribute(), ptoff, particle.velocity.data(), 3);
        }
    }

    void HQAdapter::SetGdp(GU_Detail *gdpInput) {
        gdp_ = gdpInput;
        particle_prim_ptr_ = dynamic_cast<GEO_PrimParticle *>(gdp_->appendPrimitive(GEO_PRIMPART));
        id_ref_ = gdp_->addIntTuple(GA_ATTRIB_POINT, "id", 1);
        life_ref_ = gdp_->addFloatTuple(GA_ATTRIB_POINT, "life", 2);
        vel_ref_ = gdp_->addFloatTuple(GA_ATTRIB_POINT, "v", 3);
    }
} // namespace quarks::houdini
