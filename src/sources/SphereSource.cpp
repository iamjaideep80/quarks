#include "SphereSource.h"

namespace quarks::sources {
    SphereSource::SphereSource(Scalar rate, PosVec pos, Scalar size,
                               Scalar lifeExpectancy) : Source(rate, lifeExpectancy), pos_(pos), size_(size) {
        type_ = SourceType::SPHERE_SOURCE;
    }

    std::vector<PosVec> SphereSource::RequestPositions(unsigned int time) {
        std::vector<PosVec> positions;
        positions.reserve(birth_rate_);

        for (int i = 0; i < birth_rate_; i++) {
            const Scalar theta = 2 * M_PI * (rand() / (Scalar) RAND_MAX);
            const Scalar phi = acos(1 - 2 * (rand() / (Scalar) RAND_MAX));
            const Scalar x = sin(phi) * cos(theta);
            const Scalar y = sin(phi) * sin(theta);
            const Scalar z = cos(phi);
            PosVec pos = {x * size_ + pos_[0], y * size_ + pos_[1], z * size_ + pos_[2]};
            positions.push_back(pos);
        }
        return positions;
    }
} // namespace quarks::sources
