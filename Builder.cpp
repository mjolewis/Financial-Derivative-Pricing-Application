//
// Created by Michael Lewis on 7/31/20.
//

#ifndef Builder_CPP
#define Builder_CPP

#include <iostream>

#include "Builder.hpp"

namespace MJL {
    namespace Builders {

        template<typename Input_, typename RNG_, typename Pricer_>
        Builder<Input_, RNG_, Pricer_>::Builder() {}

        template<typename Input_, typename RNG_, typename Pricer_>
        Builder<Input_, RNG_, Pricer_>::~Builder<Input_, RNG_, Pricer_>() {}

        /**
         * Build and assemble the option pricer
         * @tparam Input_
         * @tparam RNG_
         * @tparam Pricer_
         */
        template<typename Input_, typename RNG_, typename Pricer_>
        void Builder<Input_, RNG_, Pricer_ >::Build() {

            // Set up option data with input from the user
            Pricer_::
        }

        template<typename Input_, typename RNG_, typename Pricer_>
        void Builder<Input_, RNG_, Pricer_>::Finished() {
            std::cout << "\n\nBuilder has finished\n\n";
        }
    }
}

#endif // Builder_CPP
