/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Group A
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTGROUPB_HPP
#define TESTGROUPB_HPP

#include <iostream>
#include <iomanip>

#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestGroupB {
private:

    // Perpetual price is the time-homogenous price and is the same as the normal price when the expiry price T tends to infinity
    Option option1Call = Option(std::numeric_limits<double>::infinity(), 0.1, 0.1, 110, 100, 0.02, "Call", "American", "GS");
    Option option1Put = Option(std::numeric_limits<double>::infinity(), 0.1, 0.1, 110, 100, 0.02, "Put", "American", "GS");

    Pricer<Mesher, Matrix, RNG, Output> pricer;                 // Pricing engine
    Mesher mesher;                                              // Meshing engine
    Matrix matrix;                                              // Matrix engine
public:
    TestGroupB() {};
    virtual ~TestGroupB() {};

    void PartB() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group B Pricing Part B\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::cout << "\nExpiry: " << option1Call.expiry()
                  << "\nVolatility: " << option1Call.vol()
                  << "\nRisk-free rate: " << option1Call.riskFree()
                  << "\nStock price: " << option1Call.spot()
                  << "\nStrike price: " << option1Call.strike()
                  << "\nCost of carry: " << option1Call.carry()
                  << "\nExact Call Price: " << pricer.price(option1Call.expiry(), option1Call.vol(), option1Call.riskFree(),
                                                            option1Call.spot(), option1Call.strike(), option1Call.carry(),
                                                            option1Call.type(), option1Call.flavor())
                  << "\nExact Put Price: " << pricer.price(option1Put.expiry(), option1Put.vol(), option1Put.riskFree(),
                                                           option1Put.spot(), option1Put.strike(), option1Put.carry(),
                                                           option1Put.type(), option1Put.flavor())
                  << "\n";

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group B Pricing Part B\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartCAndD() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group B Pricing Part C and D\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::vector<double> mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.americanMatrix(mesh, option1Call, "S");
        std::vector<std::vector<double>> callPrices = pricer.price(options, "Call", "American");
        std::vector<std::vector<double>> putPrices = pricer.price(options, "Put", "American");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nExact prices as a function of monotonically increasing spot price:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }

        mesh = mesher.xarr(option1Call.vol(), option1Call.vol() + 1, 0.1);
        options = matrix.americanMatrix(mesh, option1Call, "sig");
        callPrices = pricer.price(options, "Call", "American");
        putPrices = pricer.price(options, "Put", "American");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nExact prices as a function of monotonically increasing volatility:\n"
                  << std::setw(15) << "Volatility"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }

        mesh = mesher.xarr(option1Call.strike(), option1Call.strike() + 5, 0.5);
        options = matrix.americanMatrix(mesh, option1Call, "K");
        callPrices = pricer.price(options, "Call", "American");
        putPrices = pricer.price(options, "Put", "American");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nExact prices as a function of monotonically increasing strike price:\n"
                  << std::setw(15) << "Strike Price"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group B Pricing Part C and D\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTGROUPB_HPP
