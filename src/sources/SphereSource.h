#ifndef SPHERESOURCE_H_
#define SPHERESOURCE_H_
#include "Source.h"

namespace quarks::sources {
    class SphereSource : public Source {
    public:
        SphereSource(Scalar rate, PosVec pos, Scalar size, Scalar lifeExpectancy);

        virtual ~SphereSource() {
        };

        std::vector<PosVec> RequestPositions(unsigned int time);

    private:
        PosVec pos_;
        Scalar size_;
    };
} // namespace quarks::sources

#endif /* SPHERESOURCE_H_ */
