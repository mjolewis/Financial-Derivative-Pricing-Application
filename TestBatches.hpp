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

class TestBS {
public:
    TestBS() {};
    virtual ~TestBS() {};

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
        std::string optFlavor;                       // European or American
        Pricer<Input, RNG, Option> pricer;           // Option to price

        // Batch 1 option data
        T = 0.25;
        sig = 0.30;
        r = 0.08;
        S = 60;
        K = 65;
        b = r;
        optFlavor = "European";

        std::cout << "\nBatch 1:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.callPrice(T, sig, r, S, K, b, optFlavor)
                  << "\nExact Put Price: " << pricer.putPrice(T, sig, r, S, K, b, optFlavor)
                  << "\n";

        // Batch 2 option data
        T = 1.0;
        sig = 0.2;
        r = 0.0;
        S = 100;
        K = 100;
        b = r;
        optFlavor = "European";

        std::cout << "\nBatch 2:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.callPrice(T, sig, r, S, K, b, optFlavor)
                  << "\nExact Put Price: " << pricer.putPrice(T, sig, r, S, K, b, optFlavor)
                  << "\n";

        // Batch 3 option data
        T = 1.0;
        sig = 0.50;
        r = 0.12;
        S = 5;
        K = 10;
        b = r;
        optFlavor = "European";

        std::cout << "\nBatch 3:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.callPrice(T, sig, r, S, K, b, optFlavor)
                  << "\nExact Put Price: " << pricer.putPrice(T, sig, r, S, K, b, optFlavor)
                  << "\n";

        // Batch 4 option data
        T = 30.0;
        sig = 0.30;
        r = 0.08;
        S = 100.0;
        K = 100.0;
        b = r;
        optFlavor = "European";

        std::cout << "\nBatch 4:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << pricer.callPrice(T, sig, r, S, K, b, optFlavor)
                  << "\nExact Put Price: " << pricer.putPrice(T, sig, r, S, K, b, optFlavor)
                  << "\n";


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Simulation complete\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif //TESTBS_HPP
