/**********************************************************************************************************************
 * Black-Scholes Option Pricer
 *
 * Testing core Batches. Separated from Main to improve readability
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTBS_HPP
#define TESTBS_HPP


#include <iostream>

#include "Input.hpp"
#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestBatches {
public:
    TestBatches() {};
    virtual ~TestBatches() {};

    void RunTest() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // Core Option data
        double T;                                          // Expiry time/maturity. E.g. T = 1 means one year
        double sig;                                        // Volatility
        double r;                                          // Risk-free interest rate
        double S;                                          // Spot price
        double K;                                          // Strike price
        double b;                                          // Cost of carry

        // Supplemental model data
        std::string call = "Call";                                   // Call option
        std::string put = "Put";                                     // Put option
        std::string optFlavor;                                       // European or American
        std::string uName;                                           // Underlying

        // Access to functionality
        Matrix matrix;                                               // Generate the matrix of options
        Mesher mesher;                                               // Generate mesh points
        Pricer<Input, RNG, Mesher> pricer;                           // Pricing engine

        // Data containers
        std::vector<double> mesh;                                    // A vector of mesh points
        std::vector<std::vector<double>> options;                    // A matrix of option data
        std::vector<std::vector<double>> callPrices;                 // A matrix of call option prices
        std::vector<std::vector<double>> putPrices;                  // A matrix of put option prices
        std::vector<std::vector<double>> callDelta;                  // A matrix of call delta prices
        std::vector<std::vector<double>> callDeltaApproximates;      // A matrix of divided differences call deltas
        std::vector<std::vector<double>> putDelta;                   // A matrix of put delta prices
        std::vector<std::vector<double>> putDeltaApproximates;       // A matrix of divided differences put deltas
        std::vector<std::vector<double>> gamma;                      // A matrix of gamma

        // Batch 1
        T = 0.25;
        sig = 0.30;
        r = 0.08;
        S = 60;
        K = 65;
        b = r;
        optFlavor = "European";
        uName = "GS";
        Option option1(T, sig, r, S, K, b, call, optFlavor, uName);

        // Generate option matrix
        mesh = mesher.xarr(S, K, .5);
        options = matrix.getMatrix(mesh, option1, "S");

        callPrices = pricer.price(options, call, optFlavor);
        putPrices = pricer.price(options, put, optFlavor);
        callDelta = pricer.delta(options, call);
        callDeltaApproximates = pricer.delta(.01, call, optFlavor, options);
        putDelta = pricer.delta(options, put);
        putDeltaApproximates = pricer.delta(.01, put, optFlavor, options);

        std::cout << "\nBatch 1:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.price(T, sig, r, S, K, b, call, optFlavor)
                  << "\nExact Put Price: " << pricer.price(T, sig, r, S, K, b, put, optFlavor)
                  << "\nCall Price determined by Put-Call Parity: " << option1.putCallParity(5.84628, put)
                  << "\nPut Price determined by Put-Call Parity: " << option1.putCallParity(2.13337, call)
                  << "\nSatisfies Put-Call Parity: " << option1.putCallParity(2.13337, 5.84628);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nOption prices and sensitivities as a function of spot price:";
        std::cout << "\nCall Price\t\tPut Price\t\tCall Delta\t\tCall Delta Appox.\t\tPut Delta\t\tPut Delta Approx";
        std::cout << "\n-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\n";
        for (int i = 0; i < callPrices.size(); ++i) {
            std::cout << callPrices[i][0] << "\t\t\t" << putPrices[i][0] << "\t\t\t"
                      << callDelta[i][0] << "\t\t" << callDeltaApproximates[i][0] << "\t\t"
                      << putDelta[i][0] << "\t\t" << putDeltaApproximates[i][0] << "\n";
        }

        // Batch 2
        T = 1.0;
        sig = 0.2;
        r = 0.0;
        S = 100;
        K = 100;
        b = r;
        optFlavor = "European";
        uName = "MS";
        Option option2(T, sig, r, S, K, b, call, optFlavor, uName);

        // Generate option matrix
        mesh = mesher.xarr(S, K, .5);
        options = matrix.getMatrix(mesh, option2, "S");

        callPrices = pricer.price(options, call, optFlavor);
        putPrices = pricer.price(options, put, optFlavor);
        callDelta = pricer.delta(options, call);
        callDeltaApproximates = pricer.delta(.01, call, optFlavor, options);
        putDelta = pricer.delta(options, put);
        putDeltaApproximates = pricer.delta(.01, put, optFlavor, options);

        std::cout << "\nBatch 2:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.price(T, sig, r, S, K, b, call, optFlavor)
                  << "\nExact Put Price: " << pricer.price(T, sig, r, S, K, b, put, optFlavor)
                  << "\nCall Price determined by Put-Call Parity: " << option2.putCallParity(7.96557, put)
                  << "\nPut Price determined by Put-Call Parity: " << option2.putCallParity(7.96557, call)
                  << "\nSatisfies Put-Call Parity: " << option2.putCallParity(2.13337, 5.84628);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nOption prices and sensitivities as a function of spot price:";
        std::cout << "\nCall Price\t\tPut Price\t\tCall Delta\t\tCall Delta Appox.\t\tPut Delta\t\tPut Delta Approx";
        std::cout << "\n-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\n";
        for (int i = 0; i < callPrices.size(); ++i) {
            std::cout << callPrices[i][0] << "\t\t\t" << putPrices[i][0] << "\t\t\t"
                      << callDelta[i][0] << "\t\t" << callDeltaApproximates[i][0] << "\t\t"
                      << putDelta[i][0] << "\t\t" << putDeltaApproximates[i][0] << "\n";
        }

        // Batch 3
        T = 1.0;
        sig = 0.50;
        r = 0.12;
        S = 5;
        K = 10;
        b = r;
        optFlavor = "European";
        uName = "C";
        Option option3(T, sig, r, S, K, b, call, optFlavor, uName);

        // Generate option matrix
        mesh = mesher.xarr(S, K, .5);
        options = matrix.getMatrix(mesh, option3, "S");

        callPrices = pricer.price(options, call, optFlavor);
        putPrices = pricer.price(options, put, optFlavor);
        callDelta = pricer.delta(options, call);
        callDeltaApproximates = pricer.delta(.01, call, optFlavor, options);
        putDelta = pricer.delta(options, put);
        putDeltaApproximates = pricer.delta(.01, put, optFlavor, options);

        std::cout << "\nBatch 3:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.price(T, sig, r, S, K, b, call, optFlavor)
                  << "\nExact Put Price: " << pricer.price(T, sig, r, S, K, b, put, optFlavor)
                  << "\nCall Price determined by Put-Call Parity: " << option3.putCallParity(4.07326, put)
                  << "\nPut Price determined by Put-Call Parity: " << option3.putCallParity(0.204058, call)
                  << "\nSatisfies Put-Call Parity: " << option3.putCallParity(0.204058, 4.07326);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nOption prices and sensitivities as a function of spot price:";
        std::cout << "\nCall Price\t\tPut Price\t\tCall Delta\t\tCall Delta Appox.\t\tPut Delta\t\tPut Delta Approx";
        std::cout << "\n-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\n";
        for (int i = 0; i < callPrices.size(); ++i) {
            std::cout << callPrices[i][0] << "\t\t\t" << putPrices[i][0] << "\t\t\t"
                      << callDelta[i][0] << "\t\t" << callDeltaApproximates[i][0] << "\t\t"
                      << putDelta[i][0] << "\t\t" << putDeltaApproximates[i][0] << "\n";
        }

        // Batch 4
        T = 30.0;
        sig = 0.30;
        r = 0.08;
        S = 100.0;
        K = 100.0;
        b = r;
        optFlavor = "European";
        uName = "JPM";
        Option option4(T, sig, r, S, K, b, call, optFlavor, uName);

        // Generate option matrix
        mesh = mesher.xarr(S, K, .5);
        options = matrix.getMatrix(mesh, option4, "S");

        callPrices = pricer.price(options, call, optFlavor);
        putPrices = pricer.price(options, put, optFlavor);
        callDelta = pricer.delta(options, call);
        callDeltaApproximates = pricer.delta(.01, call, optFlavor, options);
        putDelta = pricer.delta(options, put);
        putDeltaApproximates = pricer.delta(.01, put, optFlavor, options);

        std::cout << "\nBatch 4:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.price(T, sig, r, S, K, b, call, optFlavor)
                  << "\nExact Put Price: " << pricer.price(T, sig, r, S, K, b, put, optFlavor)
                  << "\nCall Price determined by Put-Call Parity: " << option4.putCallParity(1.2475, put)
                  << "\nPut Price determined by Put-Call Parity: " << option4.putCallParity(92.1757, call)
                  << "\nSatisfies Put-Call Parity: " << option4.putCallParity(92.1757, 1.2475);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nOption prices and sensitivities as a function of spot price:";
        std::cout << "\nCall Price\t\tPut Price\t\tCall Delta\t\tCall Delta Appox.\t\tPut Delta\t\tPut Delta Approx";
        std::cout << "\n-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\t\t-------------\n";
        for (int i = 0; i < callPrices.size(); ++i) {
            std::cout << callPrices[i][0] << "\t\t\t" << putPrices[i][0] << "\t\t\t"
                      << callDelta[i][0] << "\t\t" << callDeltaApproximates[i][0] << "\t\t"
                      << putDelta[i][0] << "\t\t" << putDeltaApproximates[i][0] << "\n";
        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Simulation complete\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::cout << "\n\nTest greeks\n\n";
        std::cout << "\nGamma: " << pricer.gamma(0.5, 0.36, 0.1, 105, 100, 0);
        std::cout << "\nCall Delta: " << pricer.delta(.5, 0.36, 0.1, 105, 100, 0, call);
        std::cout << "\nPut Delta: " << pricer.delta(.5, 0.36, 0.1, 105, 100, 0, put);
    }
};

#endif //TESTBS_HPP
