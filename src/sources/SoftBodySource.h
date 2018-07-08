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
			virtual ~SoftBodySource(){};
			inline std::vector<PosVec> requestPositions(unsigned int time)
			{
				return initPosVec;
			}
			inline PosVec requestPositions(unsigned int time,int pointNum)
			{
				return initPosVec[pointNum];
			}
			inline std::vector<bool> requestFixPoints(unsigned int time)
			{
				return fixVec;
			}
			inline SpringMap requestSpringMap(unsigned int time)
			{
				return springMap;
			}
			inline void insertSpring(int indexA, int indexB)
			{
				springMap.insert(std::pair<int, int>(indexA, indexB));
			}
			inline void insertPoint(PosVec initPos)
			{
				this->initPosVec.push_back(initPos);
				birthRate++;
			}
			inline Scalar getSpringConstant() const
			{
				return springConstant;
			}
			inline void setSpringConstant(Scalar springConstant)
			{
				this->springConstant = springConstant;
			}
			inline Scalar getDampingConstant() const
			{
				return dampingConstant;
			}
			inline void setDampingConstant(Scalar dampingConstant)
			{
				this->dampingConstant = dampingConstant;
			}
			inline bool isActive() const
			{
				return active;
			}
			inline void setActive(bool active)
			{
				this->active = active;
			}

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
