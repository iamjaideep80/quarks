#include "VDBSource.h"
#include <boost/random.hpp>

namespace quarks::sources {
    VDB_Source::VDB_Source(Scalar rate, openvdb::FloatGrid::ConstPtr ptr,
                           Scalar lifeExpectancy) : Source(rate, lifeExpectancy), grid_ptr_(ptr) {
        type_ = SourceType::VDB_SOURCE;
    }

    VDB_Source::~VDB_Source() {
        // TODO Auto-generated destructor stub
    }

    struct PointList {
        struct Point {
            double x, y, z;
        };

        std::vector<Point> list;

        void add(const openvdb::Vec3R &p) {
            Point q =
                    {p[0], p[1], p[2]};
            list.push_back(q);
        }
    };

    std::vector<PosVec> VDB_Source::RequestPositions(unsigned int time) {
        using RandGen = boost::mt11213b;
        RandGen mtRand;
        mtRand.seed(time);
        PointList points;
        openvdb::tools::UniformPointScatter<PointList, RandGen> scatter(points, (openvdb::Index64) birth_rate_, mtRand);
        scatter.operator()<openvdb::FloatGrid>(*grid_ptr_);
        std::vector<PosVec> positions;
        positions.reserve(birth_rate_);
        for (int i = 0; i < birth_rate_; i++) {
            PosVec pos(points.list[i].x, points.list[i].y, points.list[i].z);
            positions.push_back(pos);
        }
        return positions;
    }
} // namespace quarks::sources
