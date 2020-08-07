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
template<typename Input_, typename RNG_, typename Mesher_,
        template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Mesher_, Pricer_>::Builder() {}

/**
 * Initialize a new Builder
 * @throws OutOfMemoryError Indicates insufficient memory for this new Builder
 */
template<typename Input_, typename RNG_, typename Mesher_,
        template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Mesher_, Pricer_>::Builder(const Builder<Input_, RNG_, Mesher_, Pricer_> &builder) {}

/**
 * Destroy this Builder
 */
template<typename Input_, typename RNG_, typename Mesher_,
        template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Mesher_, Pricer_>::~Builder<Input_, RNG_, Mesher_, Pricer_>() {}

/**
 * Create a deep copy of the source Builder
 * @param builder The source Builder to copy from
 * @return A reference to this Builder whose members have been deeply assigned to the members of source
 */
template<typename Input_, typename RNG_, typename Mesher_,
        template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Mesher_, Pricer_> &Builder<Input_, RNG_, Mesher_, Pricer_>
::operator=(const Builder<Input_, RNG_, Mesher_, Pricer_> &builder) {
    // Avoid self assign
    if (this == &builder) { return *this; }

    // Call base class assignment
    Input_::operator=(builder);
    RNG_::operator=(builder);
    Mesher_::operator=(builder);
    Pricer_<Input_, RNG_, Mesher_>::operator=(builder);

    return *this;
}

/**
 * Build and assemble the option pricer
 */
template<typename Input_, typename RNG_, typename Mesher_,
        template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Mesher_, Pricer_>::Build() {

    // Starts the pricing engine and gets option data from the user
    double optionPrice = Pricer_<Input_, RNG_, Mesher_>::price();

    std::cout << "Option Price (delete): " << optionPrice << std::endl;
}

#endif // Builder_CPP
