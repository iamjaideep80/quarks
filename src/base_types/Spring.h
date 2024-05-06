#ifndef SPRING_H_
#define SPRING_H_

#include "Particle.h"

namespace quarks {
    struct Spring {
        Spring(Particle *in_nodeA,
               Particle *in_nodeB,
               const Scalar in_rest_length,
               const Scalar in_stiffness_constant,
               const Scalar in_damping_constant) : nodeA(in_nodeA),
                                                   nodeB(in_nodeB),
                                                   rest_length(in_rest_length),
                                                   stiffness_constant(in_stiffness_constant),
                                                   damping_constant(in_damping_constant) {
        };

        void CalculateForce(DirVec &forceA, DirVec &forceB) const {
            const DirVec vecAB = nodeB->position - nodeA->position;
            const Scalar length = vecAB.length();
            const Scalar strain_metric = (length - rest_length) / rest_length;
            const DirVec stiffness = stiffness_constant * strain_metric * vecAB / length;

            const DirVec velA = nodeA->velocity;
            const DirVec velB = nodeB->velocity;
            const DirVec velDiff = (velB - velA) / rest_length;
            const DirVec damping = damping_constant * velDiff.dot(vecAB) / length * vecAB / length;

            forceA = stiffness + damping;
            forceB = -forceA;
        }

        Particle *nodeA;
        Particle *nodeB;
        Scalar rest_length;
        Scalar stiffness_constant;
        Scalar damping_constant;
    };
} // namespace quarks

#endif /* SPRING_H_ */
