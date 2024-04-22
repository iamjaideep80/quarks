#include "ForceFactory.h"
#include "UniformForce.h"
#include "DragForce.h"
#include "NoiseForce.h"
#include "VortexForce.h"
#include "VDBForce.h"

namespace quarks::forces {
    ForcePtr ForceFactory::GetForce(const ForceData &force_data) {
        switch (force_data.type) {
            case ForceType::UNIFORM_FORCE:
                return std::make_shared<Uniform_Force>(force_data.amp, force_data.dir);
            case ForceType::DRAG_FORCE:
                return std::make_shared<Drag_Force>(force_data.amp);
            case ForceType::NOISE_FORCE:
                return std::make_shared<Noise_Force>(force_data.amp);
            case ForceType::VORTEX_FORCE:
                return std::make_shared<Vortex_Force>(force_data.amp, force_data.dir);
            case ForceType::VDB_FORCE:
                return std::make_shared<VDB_Force>(force_data.amp, force_data.dir, force_data.grid_ptr);
            default:
                std::cerr << "Error: Invalid force type encountered.\n";
                return nullptr;
        }
    }
} // namespace quarks::forces
