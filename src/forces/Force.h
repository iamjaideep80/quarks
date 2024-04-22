#ifndef FORCE_H_
#define FORCE_H_
#include "../base_types/CommonTypes.h"
#include <memory>

namespace quarks::forces {
    class Force {
    public:
        Force() = default;

        virtual ~Force() = default;

        virtual DirVec CalculateForce(PosVec pos, DirVec vel) const = 0;
    };

    using ForcePtr = std::shared_ptr<Force>;
}

#endif /* FORCE_H_ */
