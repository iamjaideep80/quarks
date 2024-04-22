#include "../base_types/CommonTypes.h"
#include "Collision.h"

#include <openvdb/math/Operators.h>
#include <openvdb/tools/Interpolation.h>


namespace quarks::collisions {
    Collision::Collision(const CollisionData &collision_data) {
        grid_ptr_ = collision_data.grid_ptr;
        gain_tangent_ = collision_data.gain_tangent;
        gain_normal_ = collision_data.gain_normal;
        outer_iso_val_ = collision_data.iso_val;
    }

    void Collision::ApplyCollision(const PosVec &old_pos, const DirVec &old_vel, PosVec &new_pos,
                                   DirVec &new_vel) const {
        const openvdb::Vec3R ijk(new_pos.x() / grid_ptr_->voxelSize().x(),
                                 new_pos.y() / grid_ptr_->voxelSize().y(),
                                 new_pos.z() / grid_ptr_->voxelSize().z());
        float sdf_val;
        openvdb::tools::PointSampler::sample(grid_ptr_->tree(), ijk, sdf_val);
        if (sdf_val < outer_iso_val_) {
            const openvdb::Coord xyz(ijk.x(), ijk.y(), ijk.z());
            openvdb::math::Vec3d grad_val = openvdb::math::ISGradient<openvdb::math::CD_2ND>::result(
                grid_ptr_->getAccessor(), xyz);
            DirVec grad_dir(grad_val.x(), grad_val.y(), grad_val.z());
            grad_dir.normalize();
            const Scalar normal_dot = new_vel.dot(grad_dir);
            const DirVec normal_comp = normal_dot * grad_dir;
            DirVec tangent_comp = new_vel - normal_comp;
            DirVec response_normal_comp = std::abs(normal_dot) * grad_dir;
            response_normal_comp = response_normal_comp * gain_normal_;
            tangent_comp = tangent_comp * gain_tangent_;
            new_vel = response_normal_comp + tangent_comp;
        }
        if (constexpr Scalar inner_iso_val = 0; sdf_val < inner_iso_val) {
            new_pos = old_pos;
        }
    }
}
