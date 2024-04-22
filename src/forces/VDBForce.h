#ifndef VDBFORCE_H_
#define VDBFORCE_H_
#include "Force.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

namespace quarks::forces {
    class VDB_Force : public Force {
    public:
        VDB_Force(const Scalar amp, const DirVec dir, openvdb::VectorGrid::ConstPtr ptr) : amplitude_(amp),
            grid_ptr_(ptr) {
        };

        ~VDB_Force() override = default;

        DirVec CalculateForce(PosVec pos, DirVec vel) const override;

    private:
        Scalar amplitude_;
        openvdb::VectorGrid::ConstPtr grid_ptr_;
    };
} // namespace quarks::forces

#endif /* VDBFORCE_H_ */
