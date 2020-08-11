/**********************************************************************************************************************
 * Black-Scholes Option Pricer
 *
 * Testing Builder Pattern. Separated from Main to improve readability
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef TESTBUILDER_HPP
#define TESTBUILDER_HPP

#include <iostream>

#include "Builder.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestBuilder {
public:
    TestBuilder() {};
    virtual ~TestBuilder() {};

    void RunTest() {

        // Begin simulation
        std::cout << "\n-------------------------------------------------------------------\n\n";
        std::cout << "\t\tBlack-Scholes Option Pricing Engine\n";
        std::cout << "\t\tAuthored By: Michael Lewis\n";
        std::cout << "\n-------------------------------------------------------------------" << std::endl;

        Builder<Input, RNG, Output, Pricer> Builder;
        Builder.Build();

        std::cout << "\n-------------------------------------------------------------------\n\n";
        std::cout << "\t\tSimulation complete";
        std::cout << "\n-------------------------------------------------------------------" << std::endl;
    }
};


#endif // TESTBUILDER_HPP
