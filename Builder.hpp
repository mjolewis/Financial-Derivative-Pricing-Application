/**********************************************************************************************************************
 * Function declarations for Builder.hpp
 *
 * Builder design pattern used to centralize the build and assembly for this option pricing application
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_HPP
#define BUILDER_HPP

namespace MJL {
    namespace Builders {

        template<typename Input_, typename RNG_, typename Pricer_>
        class Builder {
        private:
        public:
            Builder();
            virtual ~Builder();

            void Build();
        };
    }
}

#ifndef BlackScholesBuilder_CPP
#include "Builder.cpp"

#endif // BlackScholesBuilder_CPP
#endif //BUILDER_HPP
