#ifndef SOURCEFACTORY_H_
#define SOURCEFACTORY_H_
#include "Source.h"
#include "SourceData.h"

namespace quarks::sources {
    class SourceFactory {
    public:
        SourceFactory() = default;

        virtual ~SourceFactory() = default;

        static SourcePtr GetSource(const SourceData &source_data);
    };
} // namespace quarks::sources

#endif /* SOURCEFACTORY_H_ */
