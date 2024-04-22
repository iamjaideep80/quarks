#ifndef SOFTBODYSOURCE_H_
#define SOFTBODYSOURCE_H_
#include <openvdb/openvdb.h>

#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/PointScatter.h>
#include "Source.h"
#include "SoftBodyData.h"

namespace quarks::sources {
    class SoftBodySource : public Source {
    public:
        explicit SoftBodySource(const SoftBodyData &softBodyData);

        ~SoftBodySource() override = default;

        std::vector<PosVec> RequestPositions(unsigned int time) override {
            return init_pos_vec_;
        }

        PosVec RequestPosition(int pointNum) const {
            return init_pos_vec_[pointNum];
        }

        std::vector<bool> RequestFixPoints(unsigned int time) {
            return fix_vec_;
        }

        SpringMap RequestSpringMap(unsigned int time) {
            return spring_map_;
        }

        void InsertSpring(int indexA, int indexB) {
            spring_map_.insert(std::pair<int, int>(indexA, indexB));
        }

        void InsertPoint(const PosVec &initPos) {
            init_pos_vec_.push_back(initPos);
            birth_rate_++;
        }

        Scalar GetStiffnessConstant() const {
            return sprint_constant_;
        }

        void SetStiffnessConstant(const Scalar stiffness_constant) {
            sprint_constant_ = stiffness_constant;
        }

        Scalar GetDampingConstant() const {
            return damping_constant_;
        }

        void SetDampingConstant(const Scalar damping_constant) {
            damping_constant_ = damping_constant;
        }

        bool IsActive() const {
            return active_;
        }

        void SetActive(const bool active) {
            active_ = active;
        }

    private:
        std::vector<PosVec> init_pos_vec_;
        std::vector<bool> fix_vec_;
        SpringMap spring_map_;
        Scalar sprint_constant_;
        Scalar damping_constant_;
        bool active_;
    };

    using SoftBodySourcePtr = std::shared_ptr<SoftBodySource>;
} // namespace quarks::sources

#endif /* SOFTBODYSOURCE_H_ */
