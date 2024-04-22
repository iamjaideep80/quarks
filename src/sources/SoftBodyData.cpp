#include "SoftBodyData.h"


namespace quarks::sources {
    SoftBodyData::SoftBodyData(Scalar stiffness_constant, Scalar damping_constant, bool active) : stiffness_constant_(
            stiffness_constant), damping_constant_(damping_constant), active_(active) {
    }

    SoftBodyData::~SoftBodyData() = default;

    Scalar SoftBodyData::GetDampingConstant() const {
        return damping_constant_;
    }

    void SoftBodyData::SetDampingConstant(const Scalar damping_constant) {
        damping_constant_ = damping_constant;
    }

    Scalar SoftBodyData::GetStiffnessConstant() const {
        return stiffness_constant_;
    }

    void SoftBodyData::SetSpringConstant(const Scalar stiffness_constant) {
        stiffness_constant_ = stiffness_constant;
    }

    void SoftBodyData::InsertSpring(int indexA, int indexB) {
        spring_map_.insert(std::pair<int, int>(indexA, indexB));
    }

    void SoftBodyData::InsertPoint(const PosVec &initPos, const bool isFix) {
        init_pos_vec_.push_back(initPos);
        fix_vec_.push_back(isFix);
    }

    const std::vector<PosVec> &SoftBodyData::GetInitPosVec() const {
        return init_pos_vec_;
    }

    const SpringMap &SoftBodyData::GetSpringMap() const {
        return spring_map_;
    }

    const std::vector<bool> &SoftBodyData::GetFixVec() const {
        return fix_vec_;
    }

    bool SoftBodyData::IsActive() const {
        return active_;
    }

    void SoftBodyData::SetActive(const bool active) {
        active_ = active;
    }
} // namespace quarks::sources
