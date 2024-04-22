#ifndef PARTICLESYSTEM_H_
#define PARTICLESYSTEM_H_
#include <vector>
#include "../base_types/CommonTypes.h"
#include "../base_types/Particle.h"
#include "../collisions/Collision.h"
#include "../forces/Force.h"
#include "../sources/Source.h"
#include "../sources/SoftBodySource.h"
#include "../base_types/Spring.h"
#include "SourceManager.h"
#include "SoftBodyManager.h"
#include "ForceManager.h"


namespace quarks::solver {
    constexpr int MAX_NUM_PARTICLES = 10000000;

    class ParticleSystem {
    public:
        ParticleSystem();

        ~ParticleSystem() {
            InitializeSystem();
        }

        unsigned long long GetNumParticles() const {
            return particles_.size();
        }

        void InitializeSystem();

        const Particle &GetParticle(const unsigned long long index) const {
            return particles_[index];
        }

        void StepForward(Scalar time_step);

        void AddForce(forces::ForcePtr ptr) {
            force_manager_.AddForce(ptr);
        }

        void ClearForces() {
            force_manager_.ClearForces();
        }

        void AddSource(sources::SourcePtr ptr) {
            source_manager_.AddSource(ptr);
        }

        void ClearSources() {
            source_manager_.ClearSources();
        }

        void AddSoftBody(sources::SoftBodySourcePtr ptr) {
            soft_body_manager_.AddSoftBody(ptr);
        }

        void ClearSoftBodies() {
            soft_body_manager_.ClearSoftBodies();
        }

        void SetCollision(collisions::Collision *coll) {
            collision_ = coll;
            is_collision_registered_ = true;
        }

        bool IsClothSolverFlag() const;

        void SetClothSolverFlag(bool cloth_solver_flag);

    private:
        std::vector<Particle> particles_;
        std::vector<Spring> springs_;
        collisions::Collision *collision_;
        bool is_collision_registered_;

        void SolveStep(int thread_index, int num_threads, Scalar time_step);

        unsigned int steps_;
        SourceManager source_manager_;
        ForceManager force_manager_;
        SoftBodyManager soft_body_manager_;
        bool cloth_solver_flag_;
    };
}

#endif /* PARTICLESYSTEM_H_ */
