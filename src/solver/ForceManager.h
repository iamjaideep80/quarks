#ifndef FORCEMANAGER_H_
#define FORCEMANAGER_H_
#include <vector>
#include "../base_types/CommonTypes.h"

#include "../base_types/Particle.h"
#include "../base_types/Spring.h"
#include "../forces/Force.h"


namespace quarks::solver {
    class ForceManager {
    public:
        ForceManager() = default;

        virtual ~ForceManager() = default;

        void AddForce(forces::ForcePtr ptr) {
            forces_.push_back(ptr);
        };

        void ClearForces() {
            forces_.clear();
        }

        void AccumulateExternalForces(Particle &particle) const {
            for (const auto &force: forces_)
                particle.force += force->CalculateForce(particle.position, particle.velocity);
        };

        static void AccumulateInternalForces(std::vector<Spring> &springs);

    private:
        std::vector<forces::ForcePtr> forces_;
    };
} // namespace quarks::solver

#endif /* FORCEMANAGER_H_ */
