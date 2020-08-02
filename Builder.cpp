/**********************************************************************************************************************
 * Builder design pattern used to centralize the build and assembly of the Black-Scholes Option Pricer
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_CPP
#define BUILDER_CPP

#include <iostream>

#include "Builder.hpp"

template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>::Builder() {}

template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Instrument_, Pricer_>::~Builder<Input_, RNG_, Instrument_, Pricer_>() {}

/**
 * Build and assemble the option pricer
 * @tparam Input_
 * @tparam RNG_
 * @tparam Pricer_
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
