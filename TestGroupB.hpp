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
    Option option = Option(std::numeric_limits<double>::infinity(), 0.1, 0.1, 110, 100, 0.02);

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

        std::vector<std::vector<double>> prices = pricer.priceAmerican(option.expiry(), option.vol(), option.riskFree(), option.spot(),
                option.strike(), option.carry());
        std::cout << "\nExpiry: " << option.expiry()
                  << "\nVolatility: " << option.vol()
                  << "\nRisk-free rate: " << option.riskFree()
                  << "\nStock price: " << option.spot()
                  << "\nStrike price: " << option.strike()
                  << "\nCost of carry: " << option.carry() << "\n"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";

        for (const auto& row : prices) {
            std::cout << std::setw(15) << row[0]
            << std::setw(15) << row[1] << "\n";
        }

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

        std::vector<double> mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.americanMatrix(mesh, option, "S");
        std::vector<std::vector<double>> prices = pricer.priceAmerican(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nExact prices as a function of monotonically increasing spot price:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.vol(), option.vol() + 1, 0.1);
        options = matrix.americanMatrix(mesh, option, "sig");
        prices = pricer.priceAmerican(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nExact prices as a function of monotonically increasing volatility:\n"
                  << std::setw(15) << "Volatility"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.strike(), option.strike() + 5, 0.5);
        options = matrix.americanMatrix(mesh, option, "K");
        prices = pricer.priceAmerican(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nExact prices as a function of monotonically increasing strike price:\n"
                  << std::setw(15) << "Strike Price"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group B Pricing Part C and D\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTGROUPB_HPP
