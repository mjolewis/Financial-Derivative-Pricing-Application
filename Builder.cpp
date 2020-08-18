/**********************************************************************************************************************
 * Builder design pattern - Centralizes the build and assembly of the Black-Scholes Option Pricer
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_CPP
#define BUILDER_CPP

#include <iostream>

#include "Builder.hpp"
#include "TestGroupAPricing.hpp"
#include "TestGroupAGreeks.hpp"
#include "TestGroupB.hpp"

/**
 * Initialize a new Builder
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 * @throws OutOfMemoryError Indicates insufficient memory for this new Builder
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Output_, Pricer_>::Builder() : Pricer_<Input_, RNG_, Output_>() {}

/**
 * Initialize a new Builder from the source
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 * @param builder The source Builder whose data members will be copied into the new Builder
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Output_, Pricer_>::
Builder(const Builder<Input_, RNG_, Output_, Pricer_> &builder) : Pricer_<Input_, RNG_, Output_>() {}

/**
 * Destroy this Builder
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Output_, Pricer_>::~Builder<Input_, RNG_, Output_, Pricer_>() {}

/**
 * Deeply copy the source Builder
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 * @param builder The source Builder whose data members will be copied into the new Builder
 * @return A reference to this Builder whose members have been deeply assigned to the members of source
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
Builder<Input_, RNG_, Output_, Pricer_> &Builder<Input_, RNG_, Output_, Pricer_>
::operator=(const Builder<Input_, RNG_, Output_, Pricer_> &builder) {
    // Avoid self assign
    if (this == &builder) { return *this; }

    // Call base class assignment
    Input_::operator=(builder);
    RNG_::operator=(builder);
    Output_::operator=(builder);
    Pricer_<Input_, RNG_, Output_>::operator=(builder);

    return *this;
}

/**
 * Build and assemble the Black-Scholes pricing engine using the console Interface
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Output_, Pricer_>::BuildConsoleInterface() {

    // Starts the pricing engine and gets option data from the user
    double optionPrice = Pricer_<Input_, RNG_, Output_>::price();

    std::cout << "Option Price: " << optionPrice << std::endl;
}

/**
 * Build and assemble the Black-Scholes pricing engine for Test Group A
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Output_, Pricer_>::BuildGroupAPricing() {

    // Start Group A Tests
    TestGroupAPricing groupAPricing;
    groupAPricing.PartOne();
    groupAPricing.PartTwo();
    groupAPricing.PartThree();
    groupAPricing.PartFour();
}

/**
 * Build and assemble the Black-Scholes pricing engine for Test Group A
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Output_, Pricer_>::BuildGroupAGreeks() {

    // Start Group A Tests
    TestGroupAGreeks groupAGreeks;
    groupAGreeks.PartOne();
    groupAGreeks.PartTwoAndThree();
    groupAGreeks.PartFour();
}

/**
 * Build and assemble the Black-Scholes pricing engine for Test Group B
 * @tparam Input_ Provides a console interface to dynamically get option data
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @tparam Pricer_ Black-Scholes Option pricing engine
 */
template<typename Input_, typename RNG_, typename Output_, template<typename, typename, typename> class Pricer_>
void Builder<Input_, RNG_, Output_, Pricer_>::BuildGroupB() {

    // Start Group B Tests
    TestGroupB groupB;
    groupB.PartB();
    groupB.PartCAndD();
}

#endif // Builder_CPP
