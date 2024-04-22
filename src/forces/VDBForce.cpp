#include <openvdb/tools/Interpolation.h>
#include "VDBForce.h"


namespace quarks::forces {
    DirVec VDB_Force::CalculateForce(PosVec pos, DirVec vel) const {
        const openvdb::Vec3R ijk(pos.x() / grid_ptr_->voxelSize().x(), pos.y() / grid_ptr_->voxelSize().y(),
                                 pos.z() / grid_ptr_->voxelSize().z());
        openvdb::Vec3f val;
        openvdb::tools::PointSampler::sample(grid_ptr_->tree(), ijk, val);
        return amplitude_ * DirVec(val.x(), val.y(), val.z());
    }
} // namespace quarks::forces
