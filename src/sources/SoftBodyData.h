/*
 * SourceData.h
 *
 *  Created on: 22-Mar-2014
 *      Author: jaideep
 */

#ifndef SOFTBODYDATA_H_
#define SOFTBODYDATA_H_

#include "../base_types/CommonTypes.h"
using namespace quarks::base_types;
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>

namespace quarks
{
	namespace sources
	{
		class SoftBodyData
		{
		public:
			SoftBodyData(Scalar springConstant, Scalar dampingConstant,bool active);
			virtual ~SoftBodyData();
			Scalar getDampingConstant() const;
			void setDampingConstant(Scalar dampingConstant);
			Scalar getSpringConstant() const;
			void setSpringConstant(Scalar springConstant);
			void insertSpring(int indexA, int indexB);
			void insertPoint(PosVec initPos, bool isFix);
			const std::vector<PosVec>& getInitPosVec() const;
			const SpringMap& getSpringMap() const;
			const std::vector<bool>& getFixVec() const;
			bool isActive() const;
			void setActive(bool active);

		private:
			Scalar springConstant;
			Scalar dampingConstant;
			std::vector<PosVec> initPosVec;
			std::vector<bool> fixVec;
			SpringMap springMap;
			bool active;
		};
		typedef std::vector<SoftBodyData> SoftBodyDataVector;
	} /* namespace sources */
} /* namespace quarks */
#endif /* SOFTBODYDATA_H_ */
