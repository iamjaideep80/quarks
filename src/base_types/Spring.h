/*
 * Spring.h
 *
 *  Created on: 15-Mar-2014
 *      Author: jaideep
 */

#ifndef SPRING_H_
#define SPRING_H_

#include "Particle.h"

namespace quarks
{
	namespace base_types
	{
		class Spring
		{
		public:
			Spring(Particle* nodeA, Particle* nodeB, Scalar restLength, Scalar springConstant,
					Scalar dampingConstant);
			virtual ~Spring();
			void calculateForce(DirVec& forceA, DirVec& forceB);
			Particle* getNodeA() const;
			void setNodeA(Particle* nodeA);
			Particle* getNodeB() const;
			void setNodeB(Particle* nodeB);
//			Scalar getRestLength() const;
			void setRestLength(Scalar restLength);
			Scalar getSpringConstant() const;
			void setSpringConstant(Scalar springConstant);
			Scalar getDampingConstant() const;
			void setDampingConstant(Scalar dampingConstant);

		private:
			Particle* nodeA;
			Particle* nodeB;
			Scalar restLength;
			Scalar springConstant;
			Scalar dampingConstant;
		};
	} /* namespace base_types */
} /* namespace quarks */
#endif /* SPRING_H_ */
