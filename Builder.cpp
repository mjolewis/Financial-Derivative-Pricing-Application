/**********************************************************************************************************************
 * Builder design pattern used to centralize the build and assembly of the Black-Scholes Option Pricer
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_CPP
#define BUILDER_CPP

#include <iostream>

#include "Builder.hpp"

/**
 * Initialize a new Builder
 * @throws OutOfMemoryError Indicates insufficient memory for this new Builder
 */
template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>::Builder() {}

/**
 * Initialize a new Builder
 * @throws OutOfMemoryError Indicates insufficient memory for this new Builder
 */
template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>::Builder(const Builder<Input_, RNG_, Instrument_, Pricer_> &builder) {}

/**
 * Destroy this Builder
 */
template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>::~Builder<Input_, RNG_, Instrument_, Pricer_>() {}

/**
 * Assignment operator
 */
template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>& Builder
        <Input_, RNG_, Instrument_, Pricer_>::operator=(const Builder<Input_, RNG_, Instrument_, Pricer_> &builder) {
            // Avoid self assign
            if (this == &builder) { return *this; }
            return *this;
        }

/**
 * Build and assemble the option pricer
 */
template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Instrument_, Pricer_>::Build() {

    // Provides console UI to input option parameters
    Pricer_<Input_, RNG_, Instrument_>::getOptionInput();

    // Starts the pricing engine
    double optionPrice = Pricer_<Input_, RNG_, Instrument_>::price();

    std::cout << "Option Price (delete): " << optionPrice << std::endl;
}

#endif // Builder_CPP
