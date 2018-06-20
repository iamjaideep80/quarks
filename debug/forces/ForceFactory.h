/*
 * ForceFactory.h
 *
 *  Created on: 01-Mar-2014
 *      Author: jaideep
 */
#ifndef FORCEFACTORY_H_
#define FORCEFACTORY_H_
#include "Force.h"
#include "UniformForce.h"
#include "DragForce.h"
#include "NoiseForce.h"
#include "VortexForce.h"
#include "VDBForce.h"
#include "ForceData.h"
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <openvdb/tools/Interpolation.h>
namespace quarks
{
	namespace forces
	{
		class ForceFactory
		{
		public:
			ForceFactory();
			virtual ~ForceFactory();
			Force* getForce(const ForceData& forceData);
		private:
			Force* getForce(force_type type, Scalar amp, DirVec dir, openvdb::VectorGrid::Ptr gridPtr);
		};
	} /* namespace forces */
} /* namespace quarks */
#endif /* FORCEFACTORY_H_ */
