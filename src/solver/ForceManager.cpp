#include "ForceManager.h"

namespace quarks::solver {
    void ForceManager::AccumulateInternalForces(std::vector<Spring> &springs) {
        for (auto &spring: springs) {
            DirVec forceA, forceB;
            spring.CalculateForce(forceA, forceB);
            Particle *nodeA = spring.nodeA;
            nodeA->force += forceA;
            Particle *nodeB = spring.nodeB;
            nodeB->force += forceB;
        }
    }
} // namespace quarks::solver
