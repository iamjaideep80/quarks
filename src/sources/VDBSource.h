#ifndef VDBSOURCE_H_
#define VDBSOURCE_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/PointScatter.h>
#include "Source.h"

namespace quarks::sources {
    class VDB_Source : public Source {
    public:
        VDB_Source(Scalar rate, openvdb::FloatGrid::ConstPtr ptr, Scalar lifeExpectancy);

        ~VDB_Source() override = default;

        std::vector<PosVec> RequestPositions(unsigned int time) override;

    private:
        openvdb::FloatGrid::ConstPtr grid_ptr_;
    };
} // namespace quarks::sources

#endif /* VDBSOURCE_H_ */
