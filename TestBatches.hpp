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

        // Common simulation variables
        double T;                                    // Expiry time/maturity. E.g. T = 1 means one year
        double sig;                                  // Volatility
        double r;                                    // Risk-free interest rate
        double S;                                    // Spot price
        double K;                                    // Strike price
        double b;                                    // Cost of carry; b = r for Black-Scholes equity option model
        std::string call = "Call";                   // Call option
        std::string put = "Put";                     // Put option
        std::string optFlavor;                       // European or American
        std::string uName;                           // Underlying
        Pricer<Input, RNG, Option> pricer;           // Pricing engine

        // Batch 1 option data
        T = 0.25;
        sig = 0.30;
        r = 0.08;
        S = 60;
        K = 65;
        b = r;
        optFlavor = "European";
        uName = "GS";
        Option option1(T, sig, r, S, K, b, call, optFlavor, uName);

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
                  << "\nSatisfies Put-Call Parity: " << option1.putCallParity(2.13337, 5.84628)
                  << "\n";

        // Batch 2 option data
        T = 1.0;
        sig = 0.2;
        r = 0.0;
        S = 100;
        K = 100;
        b = r;
        optFlavor = "European";
        uName = "MS";
        Option option2(T, sig, r, S, K, b, call, optFlavor, uName);

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
                  << "\nSatisfies Put-Call Parity: " << option2.putCallParity(2.13337, 5.84628)
                  << "\n";

        // Batch 3 option data
        T = 1.0;
        sig = 0.50;
        r = 0.12;
        S = 5;
        K = 10;
        b = r;
        optFlavor = "European";
        uName = "C";
        Option option3(T, sig, r, S, K, b, call, optFlavor, uName);

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
                  << "\nSatisfies Put-Call Parity: " << option3.putCallParity(0.204058, 4.07326)
                  << "\n";

        // Batch 4 option data
        T = 30.0;
        sig = 0.30;
        r = 0.08;
        S = 100.0;
        K = 100.0;
        b = r;
        optFlavor = "European";
        uName = "JPM";
        Option option4(T, sig, r, S, K, b, call, optFlavor, uName);

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
                  << "\nSatisfies Put-Call Parity: " << option4.putCallParity(92.1757, 1.2475)
                  << "\n";


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Simulation complete\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif //TESTBS_HPP
