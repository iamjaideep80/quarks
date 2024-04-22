#include "SourceManager.h"
#include "../sources/SoftBodySource.h"


namespace quarks::solver {
    void SourceManager::BirthParticles(std::vector<Particle> &particles, unsigned int time) {
        for (const auto &srcPtr: sources_) {
            std::vector<PosVec> positions = srcPtr->RequestPositions(time);
            for (int j = 0; j < srcPtr->GetBirthRate(); j++) {
                particles.emplace_back(positions[j],
                                       srcPtr->GetLifeExpectancy(),
                                       max_id_);
                max_id_++;
            }
        }
    }
} // namespace quarks::solver
