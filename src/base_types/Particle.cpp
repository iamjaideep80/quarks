#include "Particle.h"
namespace quarks
{
	namespace base_types
	{
		Particle::Particle(Scalar life_expectany, unsigned int id) :
				id(id), lifeExpectancy(life_expectany)
		{
			position = 0;
			velocity = 0;
			mass = 10;
			force = 0;
			life = 0;
			isFixed = 0;
			softBodySourceNum = -1;
			softBodyPointNum = -1;
		}
		Particle::~Particle()
		{
		}
		PosVec Particle::getPosition()
		{
			return position;
		}
		void Particle::setPosition(PosVec pos)
		{
			position = pos;
		}
		PosVec Particle::getVelocity()
		{
			return velocity;
		}
		void Particle::setVelocity(PosVec vel)
		{
			velocity = vel;
		}
		Scalar Particle::getMass()
		{
			return mass;
		}
		void Particle::setMass(Scalar m)
		{
			mass = m;
		}
		DirVec Particle::getForce()
		{
			return force;
		}
		void Particle::setForce(DirVec f)
		{
			force = f;
		}
		Scalar Particle::getLifeExpectany() const
		{
			return lifeExpectancy;
		}
		void Particle::setLifeExpectany(Scalar expectany)
		{
			this->lifeExpectancy = expectany;
		}
		Scalar Particle::getLife() const
		{
			return life;
		}
		void Particle::setLife(Scalar life)
		{
			this->life = life;
		}
		void Particle::addForce(DirVec f)
		{
			force = force + f;
		}
		int64 Particle::getId() const
		{
			return id;
		}

		bool Particle::isIsFixed() const
		{
			return isFixed;
		}

		void Particle::setIsFixed(bool isFixed)
		{
			this->isFixed = isFixed;
		}

		int Particle::getSoftBodySourceNum() const
		{
			return softBodySourceNum;
		}

		void Particle::setSoftBodySourceNum(int softBodySourceNum)
		{
			this->softBodySourceNum = softBodySourceNum;
		}

		int Particle::getSoftBodyPointNum() const
		{
			return softBodyPointNum;
		}

		void Particle::setSoftBodyPointNum(int softBodyPointNum)
		{
			this->softBodyPointNum = softBodyPointNum;
		}

	}
}
