#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "CommonTypes.h"
namespace quarks
{
	namespace base_types
	{
		class Particle
		{
		public:
			Particle(Scalar life_expectany, unsigned int id);
			~Particle();
			PosVec getPosition();
			void setPosition(PosVec vel);
			DirVec getVelocity();
			void setVelocity(DirVec vel);
			Scalar getMass();
			void setMass(Scalar m);
			DirVec getForce();
			void setForce(DirVec f);
			Scalar getLifeExpectany() const;
			void setLifeExpectany(Scalar age);
			Scalar getLife() const;
			void setLife(Scalar life);
			void addForce(DirVec f);
			int64 getId() const;
			bool isIsFixed() const;
			void setIsFixed(bool isFixed);
			int getSoftBodySourceNum() const;
			void setSoftBodySourceNum(int softBodySourceNum);
			int getSoftBodyPointNum() const;
			void setSoftBodyPointNum(int softBodyPointNum);

		private:
			PosVec position;
			DirVec velocity;
			Scalar mass;
			DirVec force;
			Scalar life;
			Scalar lifeExpectancy;
			int64 id;
			bool isFixed;
			int softBodySourceNum;
			int softBodyPointNum;
		};
	}
}
#endif /* PARTICLE_H_ */
