#ifndef SOURCEMANAGER_H_
#define SOURCEMANAGER_H_
#include "../base_types/Particle.h"
#include "../sources/Source.h"


namespace quarks::solver {
    class SourceManager {
    public:
        SourceManager() {
            sources_.clear();
            max_id_ = 0;
        }

        ~SourceManager() = default;

        void BirthParticles(std::vector<Particle> &particles, unsigned int time);

        void AddSource(sources::SourcePtr ptr) {
            sources_.push_back(ptr);
        }

        void ClearSources() {
            sources_.clear();
        }

    private:
        std::vector<sources::SourcePtr> sources_;
        unsigned int max_id_;
    };
} // namespace quarks::solver

#endif /* SOURCEMANAGER_H_ */
