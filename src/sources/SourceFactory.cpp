#include "SourceFactory.h"
#include "SphereSource.h"
#include "VDBSource.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>

namespace quarks::sources {
    SourcePtr SourceFactory::GetSource(const SourceData &source_data) {
        const int rate = source_data.rate;
        const PosVec pos = source_data.pos;
        const Scalar size = source_data.size;
        const Scalar lifeExpectancy = source_data.lifeExpectancy;
        const openvdb::FloatGrid::ConstPtr ptr = source_data.grid_ptr;

        switch (source_data.type) {
            case SourceType::SPHERE_SOURCE:
                return std::make_shared<SphereSource>(rate, pos, size, lifeExpectancy);
            case SourceType::VDB_SOURCE:
                return std::make_shared<VDB_Source>(rate, ptr, lifeExpectancy);
            default:
                return std::make_shared<SphereSource>(rate, pos, size, lifeExpectancy);
        }
    }
} // namespace quarks::sources
