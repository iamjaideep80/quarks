#include "SoftBodyManager.h"
#include "../sources/SoftBodySource.h"

namespace quarks::solver {
    void SoftBodyManager::BirthParticles(std::vector<Particle> &particles,
                                         std::vector<Spring> &springs, const unsigned int time) {
        for (int soft_body_num = 0; soft_body_num < soft_bodies_.size(); soft_body_num++) {
            const sources::SoftBodySourcePtr src_ptr = soft_bodies_[soft_body_num];
            if (!src_ptr->IsActive())
                continue;
            std::vector<PosVec> positions = src_ptr->RequestPositions(time);
            std::vector<bool> fixPoints = src_ptr->RequestFixPoints(time);
            std::vector<Particle *> source_particles;
            // Create particles
            for (int pointNum = 0; pointNum < src_ptr->GetBirthRate(); pointNum++) {
                PosVec initPos(positions[pointNum][0], positions[pointNum][1], positions[pointNum][2]);
                Scalar initLifeExpectancy = src_ptr->GetLifeExpectancy();
                particles.emplace_back(initPos, initLifeExpectancy, max_id_, fixPoints[pointNum], soft_body_num,
                                       pointNum);
                source_particles.push_back(&(particles.back()));
                max_id_++;
            }
            SpringMap springMap = src_ptr->RequestSpringMap(time);
            // Create springs
            for (const auto &[first, second]: springMap) {
                Particle *nodeA = source_particles[first];
                Particle *nodeB = source_particles[second];
                DirVec vecAB = nodeA->position - nodeB->position;
                springs.emplace_back(nodeA, nodeB, vecAB.length(), src_ptr->GetStiffnessConstant(),
                                     src_ptr->GetDampingConstant());
            }
        }
    }
} // namespace quarks::solver
