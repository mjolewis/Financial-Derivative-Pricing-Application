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
        std::cout << "Test Batch: Group A Greeks Part A\n";
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

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part A\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartTwoAndThree() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part B and C\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::vector<double> mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.getFuturesOptionsMatrix(mesh, option1Call, "S");
        std::vector<std::vector<double>> callPrices = pricer.delta(options, "Call");
        std::vector<std::vector<double>> putPrices = pricer.delta(options, "Put");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nExact solution for Call and Put Delta as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }

        mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        options = matrix.getFuturesOptionsMatrix(mesh, option1Call, "S");
        callPrices = pricer.gamma(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 2:"
                  << "\nExact solution for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0] << "\n";
        }

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part B and C\n";
        std::cout << "\n*******************************************************************" << std::endl;
    };

    void PartFour() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part D\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // FDM for single option
        std::cout << "\nExpiry: " << option1Call.expiry()
                  << "\nVolatility: " << option1Call.vol()
                  << "\nRisk-free rate: " << option1Call.riskFree()
                  << "\nStock price: " << option1Call.spot()
                  << "\nStrike price: " << option1Call.strike()
                  << "\nCost of carry: " << option1Call.carry()
                  << "\nCall Delta Approximation: " << std::setprecision(7)
                  << pricer.delta(.1, option1Call.expiry(), option1Call.vol(), option1Call.riskFree(),
                                  option1Call.spot(), option1Call.strike(),
                                  option1Call.carry(), option1Call.type(), option1Call.flavor())
                  << "\nPut Delta Approximation: " << std::setprecision(7)
                  << pricer.delta(.1, option1Put.expiry(), option1Put.vol(), option1Put.riskFree(),
                                  option1Put.spot(), option1Put.strike(),
                                  option1Put.carry(), option1Put.type(), option1Put.flavor())
                  << "\n";

        // FDM for monotonically increasing Spot
        std::vector<double> mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.getFuturesOptionsMatrix(mesh, option1Call, "S");
        std::vector<std::vector<double>> callPrices = pricer.delta(.1, options, "Call", "European");
        std::vector<std::vector<double>> putPrices = pricer.delta(.1, options, "Put", "European");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nFDM approximation for Call and Put Delta for a monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }

        mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        options = matrix.getFuturesOptionsMatrix(mesh, option1Call, "S");
        callPrices = pricer.gamma(.1, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 2:"
                  << "\nFDM approximation for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0] << "\n";
        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part D\n";
        std::cout << "\n*******************************************************************" << std::endl;
    };

};

#endif //TESTGROUPAGREEKS_HPP
