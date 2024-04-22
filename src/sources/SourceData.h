#ifndef SOURCEDATA_H_
#define SOURCEDATA_H_

#include "../base_types/CommonTypes.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

#include <utility>


namespace quarks::sources {
    enum class SourceType {
        SPHERE_SOURCE, VDB_SOURCE, SOFTBODY_SOURCE
    };

    struct SourceData {
        SourceData(const SourceType type,
                   const int rate,
                   const PosVec pos,
                   const Scalar size,
                   const Scalar lifeExpectancy,
                   openvdb::FloatGrid::ConstPtr grid_ptr = nullptr) : type(type),
                                                                      rate(rate),
                                                                      pos(pos),
                                                                      size(size),
                                                                      lifeExpectancy(lifeExpectancy),
                                                                      grid_ptr(grid_ptr) {
        };
        SourceType type;
        int rate;
        PosVec pos;
        Scalar size;
        Scalar lifeExpectancy;
        openvdb::FloatGrid::ConstPtr grid_ptr;
    };

    using SourceDataVector = std::vector<SourceData>;
} // namespace quarks::sources

#endif /* SOURCEDATA_H_ */
