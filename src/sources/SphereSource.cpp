/*
 * SphereSource.cpp
 *
 *  Created on: 02-Mar-2014
 *      Author: jaideep
 */
#include <CGAL/Cartesian_d.h>
#include <CGAL/point_generators_d.h>
#include "SphereSource.h"
typedef CGAL::Cartesian_d<double> Kd;
typedef Kd::Point_d Point;
namespace quarks
{
	namespace sources
	{
		SphereSource::SphereSource(Scalar rate, PosVec pos, Scalar size, Scalar lifeExpectancy)
		{
			birthRate = rate;
			this->pos = pos;
			this->size = size;
			this->lifeExpectancy = lifeExpectancy;
			myType = SPHERE_SOURCE;
		}
		SphereSource::~SphereSource()
		{
			// TODO Auto-generated destructor stub
		}
		std::vector<PosVec> SphereSource::requestPositions(unsigned int time)
		{
			int nb_points = birthRate;
			int dim = 3;
			double size = this->size;
			std::vector<PosVec> v;
			v.reserve(nb_points);
			CGAL::Random rand(time);
			CGAL::Random_points_on_sphere_d<Point> gen(dim, size, rand);
			for (int i = 0; i < nb_points; ++i)
			{
				Point tmp_point = *gen++;
				PosVec pos(tmp_point[0], tmp_point[1], tmp_point[2]);
				v.push_back(pos + this->pos);
			}
			return v;
		}
	} /* namespace sources */
} /* namespace quarks */
