#ifndef SOURCE_H_
#define SOURCE_H_
#include <vector>
#include "SourceData.h"
#include "../base_types/CommonTypes.h"
#include <memory>


namespace quarks::sources {
    class Source {
    public:
        Source(int birthRate = 10, Scalar lifeExpectancy = 10) : birth_rate_(birthRate),
                                                                 life_expectancy_(lifeExpectancy) {
        };

        virtual ~Source() = default;

        int GetBirthRate() const {
            return birth_rate_;
        }

        void SetBirthRate(int birthRate) {
            birth_rate_ = birthRate;
        }

        Scalar GetLifeExpectancy() const {
            return life_expectancy_;
        }

        void SetLifeExpectancy(Scalar lifeExpectancy) {
            life_expectancy_ = lifeExpectancy;
        }

        SourceType GetType() const {
            return type_;
        }

        void SetType(SourceType type) {
            type_ = type;
        }

        virtual std::vector<PosVec> RequestPositions(unsigned int time) = 0;

    protected:
        int birth_rate_;
        Scalar life_expectancy_;
        SourceType type_;
    };

    using SourcePtr = std::shared_ptr<Source>;
} // namespace quarks::sources

#endif /* SOURCE_H_ */
