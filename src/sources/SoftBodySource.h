/*
 * VDBSource.h
 *
 *  Created on: 09-Mar-2014
 *      Author: jaideep
 */
#ifndef SOFTBODYSOURCE_H_
#define SOFTBODYSOURCE_H_
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
#include <openvdb/tools/PointScatter.h>
#include "Source.h"
#include "SoftBodyData.h"
namespace quarks
{
	namespace sources
	{
		class SoftBodySource : public quarks::sources::Source
		{
		public:
			SoftBodySource(SoftBodyData softBodyData);
			virtual ~SoftBodySource();
			std::vector<PosVec> requestPositions(unsigned int time);
			PosVec requestPositions(unsigned int time,int pointNum);
			std::vector<bool> requestFixPoints(unsigned int time);
			SpringMap requestSpringMap(unsigned int time);
			void insertSpring(int indexA, int indexB);
			void insertPoint(PosVec initPos);
			Scalar getSpringConstant() const;
			void setSpringConstant(Scalar springConstant);
			Scalar getDampingConstant() const;
			void setDampingConstant(Scalar dampingConstant);
			bool isActive() const;
			void setActive(bool active);

		private:
			std::vector<PosVec> initPosVec;
			std::vector<bool> fixVec;
			SpringMap springMap;
			Scalar springConstant;
			Scalar dampingConstant;
			bool active;
		};
		using SoftBodySourcePtr = std::shared_ptr<SoftBodySource>;
	} /* namespace sources */
} /* namespace quarks */
#endif /* SOFTBODYSOURCE_H_ */
