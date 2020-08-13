/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Group A
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTGROUPAGREEKS_HPP
#define TESTGROUPAGREEKS_HPP

#include <iostream>
#include <iomanip>

#include "Input.hpp"
#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestGroupAGreeks {
private:
private:
    Option option1Call = Option(0.5, 0.36, 0.1, 105, 100, 0, "Call", "European", "GS");
    Option option1Put = Option(0.5, 0.36, 0.1, 105, 100, 0, "Put", "European", "GS");

    Pricer<Input, RNG, Output> pricer;                           // Pricing engine
    Mesher mesher;                                               // Meshing engine
    Matrix matrix;                                               // Matrix engine

public:
    TestGroupAGreeks() {};
    virtual ~TestGroupAGreeks() {};

    void PartOne() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part 1\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::cout << "\nExpiry: " << option1Call.expiry()
                  << "\nVolatility: " << option1Call.vol()
                  << "\nRisk-free rate: " << option1Call.riskFree()
                  << "\nStock price: " << option1Call.spot()
                  << "\nStrike price: " << option1Call.strike()
                  << "\nCost of carry: " << option1Call.carry()
                  << "\nExact Call Delta: " << std::setprecision(7)
                  << pricer.delta(option1Call.expiry(), option1Call.vol(), option1Call.riskFree(),
                                                            option1Call.spot(), option1Call.strike(),
                                                            option1Call.carry(), option1Call.type())
                  << "\nExact Put Delta: " << std::setprecision(7)
                  << pricer.delta(option1Put.expiry(), option1Put.vol(), option1Put.riskFree(),
                                                           option1Put.spot(), option1Put.strike(),
                                                           option1Put.carry(), option1Put.type())
                  << "\n";
    }

};

#endif //TESTGROUPAGREEKS_HPP
