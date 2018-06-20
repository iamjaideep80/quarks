/*
 * VDBSource.cpp
 *
 *  Created on: 09-Mar-2014
 *      Author: jaideep
 */
#include "VDBSource.h"
#include <boost/random.hpp>
namespace quarks
{
	namespace sources
	{
		VDB_Source::VDB_Source(Scalar rate, openvdb::FloatGrid::Ptr ptr, Scalar lifeExpectancy)
		{
			birthRate = rate;
			gridPtr = ptr;
			this->lifeExpectancy = lifeExpectancy;
			myType = VDB_SOURCE;
		}
		VDB_Source::~VDB_Source()
		{
			// TODO Auto-generated destructor stub
		}
		struct PointList
		{
			struct Point
			{
				double x, y, z;
			};
			std::vector<Point> list;
			void add(const openvdb::Vec3d &p)
			{
				Point q =
				{ p[0], p[1], p[2] };
				list.push_back(q);
			}
		};
		std::vector<PosVec> VDB_Source::requestPositions(unsigned int time)
		{
			typedef boost::mt11213b RandGen;
			RandGen mtRand;
			mtRand.seed(time);
			PointList points;
			openvdb::tools::UniformPointScatter<PointList, RandGen> scatter(points, (float)birthRate, mtRand);
			scatter.operator()<openvdb::FloatGrid>(*gridPtr);
			std::vector<PosVec> v;
			v.reserve(birthRate);
			for (int i = 0; i < birthRate; i++)
			{
				PosVec pos(points.list[i].x, points.list[i].y, points.list[i].z);
				v.push_back(pos);
			}
			return v;
		}
	} /* namespace sources */
} /* namespace quarks */
