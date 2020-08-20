/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Group A
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTGROUPA_HPP
#define TESTGROUPA_HPP


#include <iostream>
#include <iomanip>

#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestGroupAPricing {
private:
    Option option1 = Option(0.25, 0.30, 0.08, 60, 65, 0.08);
    Option option2 = Option(1, 0.2, 0, 100, 100, 0);
    Option option3 = Option(1, .5, .12, 5, 10, .12);
    Option option4 = Option(30, .3, .08, 100, 100, 0.08);

    Pricer<Mesher, Matrix, RNG, Output> pricer;                 // Pricing engine
    Mesher mesher;                                              // Meshing engine
    Matrix matrix;                                              // Matrix engine

public:
    TestGroupAPricing() {};
    virtual ~TestGroupAPricing() {};

    void PartOne() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Pricing Part 1\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::cout << "\nBatch 1:"
                  << "\nExpiry: " << option1.expiry()
                  << "\nVolatility: " << option1.vol()
                  << "\nRisk-free rate: " << option1.riskFree()
                  << "\nStock price: " << option1.spot()
                  << "\nStrike price: " << option1.strike()
                  << "\nCost of carry: " << option1.carry() << "\n"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";

        std::vector<std::vector<double>> prices = pricer.priceEuropean(option1.expiry(), option1.vol(), option1.riskFree(),
                                                          option1.spot(), option1.strike(), option1.carry());

        for (const auto& row : prices) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << row[0]
                      << std::setw(15) << row[1] << "\n";
        }
//        for (int i = 0; i < prices.size(); ++i) {
//            std::cout << std::setprecision(6)
//                      << std::setw(15) << prices[0]
//                      << std::setw(15) << prices[1] << "\n";
//        }

        // Batch 2
        std::cout << "\n\nBatch 2:"
                << "\nExpiry: " << option2.expiry()
                << "\nVolatility: " << option2.vol()
                << "\nRisk-free rate: " << option2.riskFree()
                << "\nStock price: " << option2.spot()
                << "\nStrike price: " << option2.strike()
                << "\nCost of carry: " << option2.carry() << "\n"
                << std::setw(15) << "Call Price"
                << std::setw(15) << "Put Price\n"
                << std::setw(15) << "-----------"
                << std::setw(15) << "-----------\n";

        prices = pricer.priceEuropean(option2.expiry(), option2.vol(), option2.riskFree(), option2.spot(),
                                      option2.strike(), option2.carry());

        for (const auto& row : prices) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << row[0]
                      << std::setw(15) << row[1] << "\n";
        }

//        for (int i = 0; i < prices.size(); ++i) {
//            std::cout << std::setprecision(6)
//                      << std::setw(15) << prices[0]
//                      << std::setw(15) << prices[1] << "\n";
//        }

        // Batch 3
        std::cout << "\n\nBatch 3:"
                << "\nExpiry: " << option3.expiry()
                << "\nVolatility: " << option3.vol()
                << "\nRisk-free rate: " << option3.riskFree()
                << "\nStock price: " << option3.spot()
                << "\nStrike price: " << option3.strike()
                << "\nCost of carry: " << option3.carry() << "\n"
                << std::setw(15) << "Call Price"
                << std::setw(15) << "Put Price\n"
                << std::setw(15) << "-----------"
                << std::setw(15) << "-----------\n";

        prices = pricer.priceEuropean(option3.expiry(), option3.vol(), option3.riskFree(), option3.spot(),
                                      option3.strike(), option3.carry());

        for (const auto& row : prices) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << row[0]
                      << std::setw(15) << row[1] << "\n";
        }

//        for (int i = 0; i < prices.size(); ++i) {
//            std::cout << std::setprecision(6)
//                      << std::setw(15) << prices[0]
//                      << std::setw(15) << prices[1] << "\n";
//        }

        // Batch 4
        std::cout << "\n\nBatch 4:"
                << "\nExpiry: " << option4.expiry()
                << "\nVolatility: " << option4.vol()
                << "\nRisk-free rate: " << option4.riskFree()
                << "\nStock price: " << option4.spot()
                << "\nStrike price: " << option4.strike()
                << "\nCost of carry: " << option4.carry() << "\n"
                << std::setw(15) << "Call Price"
                << std::setw(15) << "Put Price\n"
                << std::setw(15) << "-----------"
                << std::setw(15) << "-----------\n";

        prices = pricer.priceEuropean(option4.expiry(), option4.vol(), option4.riskFree(), option4.spot(),
                                      option4.strike(), option4.carry());

        for (const auto& row : prices) {
            std::cout << std::setprecision(6)
                      << std::setw(15) << row[0]
                      << std::setw(15) << row[1] << "\n";
        }

//        for (int i = 0; i < prices.size(); ++i) {
//            std::cout << std::setprecision(6)
//                      << std::setw(15) << prices[0]
//                      << std::setw(15) << prices[1] << "\n";
//        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Pricing Part 1\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartTwo() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Pricing Part 2\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // Batch 1
        std::cout << "\nBatch 1:"
                  << "\nExpiry: " << option1.expiry()
                  << "\nVolatility: " << option1.vol()
                  << "\nRisk-free rate: " << option1.riskFree()
                  << "\nStock price: " << option1.spot()
                  << "\nStrike price: " << option1.strike()
                  << "\nCost of carry: " << option1.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option1.putCallParity(5.84628, "Put")
                  << "\nPut Price determined by Put-Call Parity: " << option1.putCallParity(2.13337, "Call")
                  << "\nSatisfies Put-Call Parity: " << option1.putCallParity(2.13337, 5.84628);

        // Batch 2
        std::cout << "\n\nBatch 2:"
                  << "\nExpiry: " << option2.expiry()
                  << "\nVolatility: " << option2.vol()
                  << "\nRisk-free rate: " << option2.riskFree()
                  << "\nStock price: " << option2.spot()
                  << "\nStrike price: " << option2.strike()
                  << "\nCost of carry: " << option2.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option2.putCallParity(7.96557, "Put")
                  << "\nPut Price determined by Put-Call Parity: " << option2.putCallParity(7.96557, "Call")
                  << "\nSatisfies Put-Call Parity: " << option2.putCallParity(7.96557, 7.96557);

        // Batch 3
        std::cout << "\n\nBatch 3:"
                  << "\nExpiry: " << option3.expiry()
                  << "\nVolatility: " << option3.vol()
                  << "\nRisk-free rate: " << option3.riskFree()
                  << "\nStock price: " << option3.spot()
                  << "\nStrike price: " << option3.strike()
                  << "\nCost of carry: " << option3.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option3.putCallParity(4.07326, "Put")
                  << "\nPut Price determined by Put-Call Parity: " << option3.putCallParity(0.204058, "Call")
                  << "\nSatisfies Put-Call Parity: " << option3.putCallParity(0.204058, 4.07326);

        // Batch 4
        std::cout << "\n\nBatch 4:"
                  << "\nExpiry: " << option4.expiry()
                  << "\nVolatility: " << option4.vol()
                  << "\nRisk-free rate: " << option4.riskFree()
                  << "\nStock price: " << option4.spot()
                  << "\nStrike price: " << option4.strike()
                  << "\nCost of carry: " << option4.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option4.putCallParity(1.2475, "Put")
                  << "\nPut Price determined by Put-Call Parity: " << option4.putCallParity(92.1757, "Call")
                  << "\nSatisfies Put-Call Parity: " << option4.putCallParity(92.1757, 1.2475);

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Pricing Part 2\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartThree() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Pricing Part 3\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // Batch 1
        std::vector<double> mesh = mesher.xarr(option1.spot(), option1.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.europeanMatrix(mesh, option1, "S");
        std::vector<std::vector<double>> prices = pricer.priceEuropean(options);

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
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        // Batch 2
        mesh = mesher.xarr(option2.spot(), option2.spot() + 5, 0.5);
        options = matrix.europeanMatrix(mesh, option2, "S");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 2:"
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
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        // Batch 3
        mesh = mesher.xarr(option3.spot(), option3.spot() + 5, 0.5);
        options = matrix.europeanMatrix(mesh, option3, "S");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 3:"
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
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        // Batch 4
        mesh = mesher.xarr(option4.spot(), option4.spot() + 5, 0.5);
        options = matrix.europeanMatrix(mesh, option4, "S");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 4:"
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
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Pricing Part 3\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartFour() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Pricing Part 4\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // Batch 1
        std::vector<double> mesh = mesher.xarr(option1.expiry(), option1.expiry() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.europeanMatrix(mesh, option1, "T");
        std::vector<std::vector<double>> prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nOption prices as a function of monotonically increasing Expiry:\n"
                  << std::setw(15) << "Expiry"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        // Batch 2
        mesh = mesher.xarr(option2.vol(), option2.vol() + 5, 0.5);
        options = matrix.europeanMatrix(mesh, option2, "sig");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 2:"
                  << "\nOption prices as a function of monotonically increasing Volatility:\n"
                  << std::setw(15) << "Volatility"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        // Batch 3
        mesh = mesher.xarr(option3.strike(), option3.strike() + 5, 0.5);
        options = matrix.europeanMatrix(mesh, option3, "K");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 3:"
                  << "\nOption prices as a function of monotonically increasing Strike:\n"
                  << std::setw(15) << "Strike Price"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        // Batch 4
        mesh = mesher.xarr(option4.riskFree(), option4.riskFree() + .05, 0.005);
        options = matrix.europeanMatrix(mesh, option4, "r");
        prices = pricer.priceEuropean(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 4:"
                  << "\nOption prices as a function of monotonically increasing Risk Free Rate:\n"
                  << std::setw(15) << "Risk-Free"
                  << std::setw(15) << "Call Price"
                  << std::setw(15) << "Put Price\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        };

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Pricing Part 4\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTGROUPA_HPP
