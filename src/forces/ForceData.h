#ifndef FORCEDATA_H_
#define FORCEDATA_H_
#include "../base_types/CommonTypes.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

namespace quarks::forces {
    enum class ForceType {
        UNIFORM_FORCE, DRAG_FORCE, NOISE_FORCE, VORTEX_FORCE, VDB_FORCE
    };

    struct ForceData {
        ForceData(const ForceType type,
                  const Scalar amp, const DirVec dir,
                  const openvdb::VectorGrid::ConstPtr &grid_ptr) : type(type),
                                                                   amp(amp),
                                                                   dir(dir),
                                                                   grid_ptr(grid_ptr) {
        };
        ForceType type;
        Scalar amp;
        DirVec dir;
        openvdb::VectorGrid::ConstPtr grid_ptr;
    };

    using ForceDataVector = std::vector<ForceData>;
} // namespace quarks::forces

#endif /* FORCEDATA_H_ */
