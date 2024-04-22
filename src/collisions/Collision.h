#ifndef COLLISION_H_
#define COLLISION_H_

#include "CollisionData.h"

namespace quarks::collisions {
    class Collision {
    public:
        explicit Collision(const CollisionData &collision_data);

        ~Collision() = default;

        const openvdb::FloatGrid::ConstPtr &getGridPtr() const {
            return grid_ptr_;
        }

        void ApplyCollision(const PosVec &old_pos, const DirVec &old_vel, PosVec &new_pos, DirVec &new_vel) const;

    private:
        openvdb::FloatGrid::ConstPtr grid_ptr_;
        Scalar gain_tangent_;
        Scalar gain_normal_;
        Scalar outer_iso_val_;
    };
}
#endif /* COLLISION_H_ */
