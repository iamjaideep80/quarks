#ifndef FORCEFACTORY_H_
#define FORCEFACTORY_H_
#include "Force.h"
#include "ForceData.h"

namespace quarks::forces {
    class ForceFactory {
    public:
        ForceFactory() = default;

        ~ForceFactory() = default;

        static ForcePtr GetForce(const ForceData &force_data);
    };
} // namespace quarks::forces

#endif /* FORCEFACTORY_H_ */
