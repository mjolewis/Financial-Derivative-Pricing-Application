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

#include "EuropeanOption.hpp"

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
        EuropeanOption euroOption;                   // Option to price

        // Batch 1 option data
        T = 0.25;                                    // Expiry time/maturity. E.g. T = 1 means one year
        sig = 0.30;                                  // Volatility
        r = 0.08;                                    // Risk-free interest rate
        S = 60;                                      // Spot price
        K = 65;                                      // Strike price
        b = r;                                       // Cost of carry; b = r for Black-Scholes equity option model

        std::cout << "\nBatch 1:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << euroOption.callPrice(T, sig, r, S, K, b)
                  << "\nExact Put Price: " << euroOption.putPrice(T, sig, r, S, K, b)
                  << "\n";

        // Batch 2 option data
        T = 1.0;                                     // Expiry time/maturity. E.g. T = 1 means one year
        sig = 0.2;                                   // Volatility
        r = 0.0;                                     // Risk-free interest rate
        S = 100;                                     // Spot price
        K = 100;                                     // Strike price
        b = r;                                       // Cost of carry; b = r for Black-Scholes equity option model

        std::cout << "\nBatch 2:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << euroOption.callPrice(T, sig, r, S, K, b)
                  << "\nExact Put Price: " << euroOption.putPrice(T, sig, r, S, K, b)
                  << "\n";

        // Batch 3 option data
        T = 1.0;                                     // Expiry time/maturity. E.g. T = 1 means one year
        sig = 0.50;                                  // Volatility
        r = 0.12;                                    // Risk-free interest rate
        S = 5;                                       // Spot price
        K = 10;                                      // Strike price
        b = r;                                       // Cost of carry; b = r for Black-Scholes equity option model

        std::cout << "\nBatch 3:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << euroOption.callPrice(T, sig, r, S, K, b)
                  << "\nExact Put Price: " << euroOption.putPrice(T, sig, r, S, K, b)
                  << "\n";

        // Batch 4 option data
        T = 30.0;                                    // Expiry time/maturity. E.g. T = 1 means one year
        sig = 0.30;                                  // Volatility
        r = 0.08;                                    // Risk-free interest rate
        S = 100.0;                                   // Spot price
        K = 100.0;                                   // Strike price
        b = r;                                       // Cost of carry; b = r for Black-Scholes equity option model

        std::cout << "\nBatch 4:"
                  << "\nExpiry: " << T
                  << "\nVolatility: " << sig
                  << "\nRisk-free rate: " << r
                  << "\nStock price: " << S
                  << "\nStrike price: " << K
                  << "\nCost of carry: " << b
                  << "\nExact Call Price: " << euroOption.callPrice(T, sig, r, S, K, b)
                  << "\nExact Put Price: " << euroOption.putPrice(T, sig, r, S, K, b)
                  << "\n";


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Simulation complete\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif //TESTBS_HPP
