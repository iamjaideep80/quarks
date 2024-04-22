#ifndef SOFTBODYDATA_H_
#define SOFTBODYDATA_H_

#include "../base_types/CommonTypes.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>


namespace quarks::sources {
    class SoftBodyData {
    public:
        SoftBodyData(Scalar stiffness_constant, Scalar damping_constant, bool active);

        virtual ~SoftBodyData();

        Scalar GetDampingConstant() const;

        void SetDampingConstant(Scalar damping_constant);

        Scalar GetStiffnessConstant() const;

        void SetSpringConstant(Scalar stiffness_constant);

        void InsertSpring(int indexA, int indexB);

        void InsertPoint(const PosVec &initPos, bool isFix);

        const std::vector<PosVec> &GetInitPosVec() const;

        const SpringMap &GetSpringMap() const;

        const std::vector<bool> &GetFixVec() const;

        bool IsActive() const;

        void SetActive(bool active);

    private:
        Scalar stiffness_constant_;
        Scalar damping_constant_;
        std::vector<PosVec> init_pos_vec_;
        std::vector<bool> fix_vec_;
        SpringMap spring_map_;
        bool active_;
    };

    using SoftBodyDataVector = std::vector<SoftBodyData>;
} // namespace quarks::sources

#endif /* SOFTBODYDATA_H_ */
