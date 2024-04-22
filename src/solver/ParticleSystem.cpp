#include "ParticleSystem.h"
#include "OdeSolver.h"
#include <thread>

namespace quarks::solver {
    ParticleSystem::ParticleSystem(): collision_(nullptr), is_collision_registered_(false), steps_(0),
                                      cloth_solver_flag_(false) {
        particles_.reserve(MAX_NUM_PARTICLES);
        InitializeSystem();
    }

    void ParticleSystem::InitializeSystem() {
        particles_.clear();
        springs_.clear();
        steps_ = 0;
    }

    bool ParticleSystem::IsClothSolverFlag() const {
        return cloth_solver_flag_;
    }

    void ParticleSystem::SetClothSolverFlag(const bool cloth_solver_flag) {
        cloth_solver_flag_ = cloth_solver_flag;
    }

    void ParticleSystem::StepForward(Scalar time_step) {
        source_manager_.BirthParticles(particles_, steps_);
        soft_body_manager_.BirthParticles(particles_, springs_, steps_);
        ForceManager::AccumulateInternalForces(springs_);

        unsigned int num_of_threads = std::thread::hardware_concurrency() - 1;
        if (num_of_threads == 0)
            num_of_threads = 1;

        std::vector<std::thread> threads;
        for (unsigned i = 0; i < num_of_threads; i++)
            threads.emplace_back(&ParticleSystem::SolveStep, this, i, num_of_threads, time_step);

        for (auto &thread: threads)
            thread.join();

        steps_++;
    }

    void ParticleSystem::SolveStep(const int thread_index, const int num_threads, const Scalar time_step) {
        for (int i = thread_index; i < particles_.size(); i += num_threads) {
            Particle &particle = particles_[i];
            if (particle.life > particle.life_expectancy) {
                continue;
            }

            force_manager_.AccumulateExternalForces(particle);

            PosVec old_pos = particle.position;
            DirVec old_vel = particle.velocity;
            DirVec old_acc = particle.force / particle.mass;
            PosVec new_pos;
            DirVec new_vel;

            if (particle.is_fixed) {
                new_pos = soft_body_manager_.GetConstraintPos(particle.soft_body_source_num,
                                                              particle.soft_body_point_num);
                particle.position = new_pos;
                particle.velocity = (new_pos - old_pos) / time_step;
                continue;
            }

            if (cloth_solver_flag_)
                OdeSolver::ApplyRK4(time_step, old_pos, old_vel, old_acc, new_pos, new_vel);
            else
                OdeSolver::ApplyEuler(time_step, old_pos, old_vel, old_acc, new_pos, new_vel);

            if (is_collision_registered_)
                collision_->ApplyCollision(old_pos, old_vel, new_pos, new_vel);

            particle.position = new_pos;
            particle.velocity = new_vel;
            particle.life++;
            particle.force = 0;
        }
    }
}
