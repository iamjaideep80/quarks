#include "SoftBodySource.h"

namespace quarks::sources {
    SoftBodySource::SoftBodySource(const SoftBodyData &softBodyData) {
        life_expectancy_ = INT_MAX;
        sprint_constant_ = softBodyData.GetStiffnessConstant();
        damping_constant_ = softBodyData.GetDampingConstant();
        type_ = SourceType::SOFTBODY_SOURCE;
        init_pos_vec_ = softBodyData.GetInitPosVec();
        fix_vec_ = softBodyData.GetFixVec();
        spring_map_ = softBodyData.GetSpringMap();
        birth_rate_ = static_cast<int>(init_pos_vec_.size());
        active_ = softBodyData.IsActive();
    }
} // namespace quarks::sources
