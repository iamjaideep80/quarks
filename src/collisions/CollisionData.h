#ifndef COLLISIONDATA_H_
#define COLLISIONDATA_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <utility>
#include "../base_types/CommonTypes.h"

namespace quarks::collisions {
    struct CollisionData {
        CollisionData(openvdb::FloatGrid::ConstPtr grid_ptr,
                      const Scalar in_gain_tangent,
                      const Scalar in_gain_normal,
                      const Scalar in_iso_val) : grid_ptr(std::move(grid_ptr)),
                                                 gain_tangent(in_gain_tangent),
                                                 gain_normal(in_gain_normal),
                                                 iso_val(in_iso_val) {
        };
        openvdb::FloatGrid::ConstPtr grid_ptr;
        Scalar gain_tangent;
        Scalar gain_normal;
        Scalar iso_val;
    };

    using CollisionDataVector = std::vector<CollisionData>;
}
#endif /* COLLISIONDATA_H_ */
