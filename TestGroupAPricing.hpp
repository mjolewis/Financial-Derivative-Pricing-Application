/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Group A
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTGROUPA_HPP
#define TESTGROUPA_HPP


#include <iostream>
#include <iomanip>

#include "Input.hpp"
#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestGroupAPricing {
private:
    Option option1Call = Option(0.25, 0.30, 0.08, 60, 65, 0.08, "Call", "European", "GS");
    Option option1Put = Option(0.25, 0.30, 0.08, 60, 65, 0.08, "Put", "European", "GS");

    Option option2Call = Option(1, 0.2, 0, 100, 100, 0, "Call", "European", "MS");
    Option option2Put = Option(1, 0.2, 0, 100, 100, 0, "Put", "European", "MS");

    Option option3Call = Option(1, .5, .12, 5, 10, .12, "Call", "European", "C");
    Option option3Put = Option(1, .5, .12, 5, 10, .12, "Put", "European", "C");

    Option option4Call = Option(30, .3, .08, 100, 100, 0.08, "Call", "European", "JPM");
    Option option4Put = Option(30, .3, .08, 100, 100, 0.08, "Put", "European", "JPM");

    Pricer<Input, RNG, Output> pricer;                           // Pricing engine
    Mesher mesher;                                               // Meshing engine
    Matrix matrix;                                               // Matrix engine

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
                  << "\nExpiry: " << option1Call.expiry()
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
                                                           option1Put.type(), option1Put.flavor());

        // Batch 2
        std::cout << "\n\nBatch 2:"
                  << "\nExpiry: " << option2Call.expiry()
                  << "\nVolatility: " << option2Call.vol()
                  << "\nRisk-free rate: " << option2Call.riskFree()
                  << "\nStock price: " << option2Call.spot()
                  << "\nStrike price: " << option2Call.strike()
                  << "\nCost of carry: " << option2Call.carry()
                  << "\nExact Call Price: " << pricer.price(option2Call.expiry(), option2Call.vol(), option2Call.riskFree(),
                                                            option2Call.spot(), option2Call.strike(), option2Call.carry(),
                                                            option2Call.type(), option2Call.flavor())
                  << "\nExact Put Price: " << pricer.price(option2Put.expiry(), option2Put.vol(), option2Put. riskFree(),
                                                           option2Put.spot(), option2Put.strike(), option2Put.carry(),
                                                           option2Put.type(), option2Put.flavor());

        // Batch 3
        std::cout << "\n\nBatch 3:"
                  << "\nExpiry: " << option3Call.expiry()
                  << "\nVolatility: " << option3Call.vol()
                  << "\nRisk-free rate: " << option3Call.riskFree()
                  << "\nStock price: " << option3Call.spot()
                  << "\nStrike price: " << option3Call.strike()
                  << "\nCost of carry: " << option3Call.carry()
                  << "\nExact Call Price: " << pricer.price(option3Call.expiry(), option3Call.vol(), option3Call. riskFree(),
                                                            option3Call.spot(), option3Call.strike(), option3Call.carry(),
                                                            option3Call.type(), option3Call.flavor())
                  << "\nExact Put Price: " << pricer.price(option3Put.expiry(), option3Put.vol(), option3Put.riskFree(),
                                                           option3Put.spot(), option3Put.strike(), option3Put.carry(),
                                                           option3Put.type(), option3Put.flavor());

        // Batch 4
        std::cout << "\n\nBatch 4:"
                  << "\nExpiry: " << option4Call.expiry()
                  << "\nVolatility: " << option4Call.vol()
                  << "\nRisk-free rate: " << option4Call.riskFree()
                  << "\nStock price: " << option4Call.spot()
                  << "\nStrike price: " << option4Call.strike()
                  << "\nCost of carry: " << option4Call.carry()
                  << "\nExact Call Price: " << pricer.price(option4Call.expiry(), option4Call.vol(), option4Call. riskFree(),
                                                            option4Call.spot(), option4Call.strike(), option4Call.carry(),
                                                            option4Call.type(), option4Call.flavor())
                  << "\nExact Put Price: " << pricer.price(option4Put.expiry(), option4Put.vol(), option4Put.riskFree(),
                                                           option4Put.spot(), option4Put.strike(), option4Put.carry(),
                                                           option4Put.type(), option4Put.flavor());


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
                  << "\nExpiry: " << option1Call.expiry()
                  << "\nVolatility: " << option1Call.vol()
                  << "\nRisk-free rate: " << option1Call.riskFree()
                  << "\nStock price: " << option1Call.spot()
                  << "\nStrike price: " << option1Call.strike()
                  << "\nCost of carry: " << option1Call.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option1Put.putCallParity(5.84628, option1Put.type())
                  << "\nPut Price determined by Put-Call Parity: " << option1Call.putCallParity(2.13337, option1Call.type())
                  << "\nSatisfies Put-Call Parity: " << option1Call.putCallParity(2.13337, 5.84628);

        // Batch 2
        std::cout << "\n\nBatch 2:"
                  << "\nExpiry: " << option2Call.expiry()
                  << "\nVolatility: " << option2Call.vol()
                  << "\nRisk-free rate: " << option2Call.riskFree()
                  << "\nStock price: " << option2Call.spot()
                  << "\nStrike price: " << option2Call.strike()
                  << "\nCost of carry: " << option2Call.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option2Put.putCallParity(7.96557, option2Put.type())
                  << "\nPut Price determined by Put-Call Parity: " << option2Call.putCallParity(7.96557, option2Call.type())
                  << "\nSatisfies Put-Call Parity: " << option2Call.putCallParity(7.96557, 7.96557);

        // Batch 3
        std::cout << "\n\nBatch 3:"
                  << "\nExpiry: " << option3Call.expiry()
                  << "\nVolatility: " << option3Call.vol()
                  << "\nRisk-free rate: " << option3Call.riskFree()
                  << "\nStock price: " << option3Call.spot()
                  << "\nStrike price: " << option3Call.strike()
                  << "\nCost of carry: " << option3Call.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option3Put.putCallParity(4.07326, option3Put.type())
                  << "\nPut Price determined by Put-Call Parity: " << option3Call.putCallParity(0.204058, option3Call.type())
                  << "\nSatisfies Put-Call Parity: " << option3Call.putCallParity(0.204058, 4.07326);

        // Batch 4
        std::cout << "\n\nBatch 4:"
                  << "\nExpiry: " << option4Call.expiry()
                  << "\nVolatility: " << option4Call.vol()
                  << "\nRisk-free rate: " << option4Call.riskFree()
                  << "\nStock price: " << option4Call.spot()
                  << "\nStrike price: " << option4Call.strike()
                  << "\nCost of carry: " << option4Call.carry()
                  << "\nCall Price determined by Put-Call Parity: " << option4Put.putCallParity(1.2475, option4Put.type())
                  << "\nPut Price determined by Put-Call Parity: " << option4Call.putCallParity(92.1757, option4Call.type())
                  << "\nSatisfies Put-Call Parity: " << option4Call.putCallParity(92.1757, 1.2475);

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
        std::vector<double> mesh = mesher.xarr(option1Call.spot(), option1Call.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.getStockOptionsMatrix(mesh, option1Call, "S");
        std::vector<std::vector<double>> callPrices = pricer.price(options, "Call", "European");
        std::vector<std::vector<double>> putPrices = pricer.price(options, "Put", "European");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 1:"
                  << "\nOption prices as a function of monotonically increasing spot price:\n"
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

        // Batch 2
        mesh = mesher.xarr(option2Call.spot(), option2Call.spot() + 5, 0.5);
        options = matrix.getStockOptionsMatrix(mesh, option2Call, "S");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 2:"
                  << "\nOption prices as a function of monotonically increasing spot price:\n"
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
        };

        // Batch 3
        mesh = mesher.xarr(option3Call.spot(), option3Call.spot() + 5, 0.5);
        options = matrix.getStockOptionsMatrix(mesh, option3Call, "S");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 3:"
                  << "\nOption prices as a function of monotonically increasing spot price:\n"
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
        };

        // Batch 4
        mesh = mesher.xarr(option4Call.spot(), option4Call.spot() + 5, 0.5);
        options = matrix.getStockOptionsMatrix(mesh, option4Call, "S");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nBatch 4:"
                  << "\nOption prices as a function of monotonically increasing spot price:\n"
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
        std::vector<double> mesh = mesher.xarr(option1Call.expiry(), option1Call.expiry() + 5, 0.5);
        std::vector<std::vector<double>> options = matrix.getStockOptionsMatrix(mesh, option1Call, "T");
        std::vector<std::vector<double>> callPrices = pricer.price(options, "Call", "European");
        std::vector<std::vector<double>> putPrices = pricer.price(options, "Put", "European");

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
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        }

        // Batch 2
        mesh = mesher.xarr(option2Call.vol(), option2Call.vol() + 5, 0.5);
        options = matrix.getStockOptionsMatrix(mesh, option2Call, "sig");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

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
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        };

        // Batch 3
        mesh = mesher.xarr(option3Call.strike(), option3Call.strike() + 5, 0.5);
        options = matrix.getStockOptionsMatrix(mesh, option3Call, "K");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

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
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        };

        // Batch 4
        mesh = mesher.xarr(option4Call.riskFree(), option4Call.riskFree() + .05, 0.005);
        options = matrix.getStockOptionsMatrix(mesh, option4Call, "r");
        callPrices = pricer.price(options, "Call", "European");
        putPrices = pricer.price(options, "Put", "European");

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
                      << std::setw(15) << callPrices[i][0]
                      << std::setw(15) << putPrices[i][0] << "\n";
        };

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Pricing Part 4\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTGROUPA_HPP
