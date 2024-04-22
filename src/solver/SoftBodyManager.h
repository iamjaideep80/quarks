#ifndef SOFTBODYMANAGER_H_
#define SOFTBODYMANAGER_H_
#include "../base_types/CommonTypes.h"
#include "../base_types/Particle.h"
#include "../base_types/Spring.h"
#include "../sources/Source.h"
#include "../sources/SoftBodySource.h"
#include <map>

namespace quarks::solver {
    class SoftBodyManager {
    public:
        SoftBodyManager() {
            soft_bodies_.clear();
            max_id_ = 0;
        }

        ~SoftBodyManager() = default;

        void BirthParticles(std::vector<Particle> &particles, std::vector<Spring> &springs,
                            unsigned int time);

        void AddSoftBody(sources::SoftBodySourcePtr ptr) {
            soft_bodies_.push_back(ptr);
        }

        void ClearSoftBodies() {
            soft_bodies_.clear();
        }

        PosVec GetConstraintPos(const int softBodyNum, const int pointNum) const {
            return soft_bodies_[softBodyNum]->RequestPosition(pointNum);
        }

    private:
        std::vector<sources::SoftBodySourcePtr> soft_bodies_;
        unsigned int max_id_;
        std::map<int, std::vector<Particle *> > src_map_;
    };
} // namespace quarks::solver

#endif /* SOFTBODYMANAGER_H_ */
