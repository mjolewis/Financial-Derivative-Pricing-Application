/**********************************************************************************************************************
 * A financial instrument
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>
#include <cmath>

#include "Instrument.hpp"

class Option : public Instrument {
private:

    // Required option data
    double T;                                    // Expiry time/maturity. E.g. T = 1 means one year
    double sig;                                  // Volatility
    double r;                                    // Risk-free interest rate
    double S;                                    // Spot price
    double K;                                    // Strike price
    double b;                                    // Cost of carry; b = r for Black-Scholes equity option model

    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    static bool putCallParity(double C, double P, double T_, double K, double r_, double S);

public:

    // Constructors and Destructors
    Option();
    Option(double T_, double sig_, double r_, double S_, double K_, double b_);
    Option(const Option &source);
    virtual ~Option();

    // Operator overloading
    Option &operator=(const Option &source);

    // Mechanism to calculate the call (or put) price for a corresponding put (or call) price
    double putCallParity(double optionPrice, const std::string& optType_) const;

    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    bool putCallParity(double callPrice, double putPrice) const;

    // Getters
    double expiry() const;
    double vol() const;
    double riskFree() const;
    double spot() const;
    double strike() const;
    double carry() const;

    // Setters
    void setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_);
    void expiry(double T_);
    void vol(double sig_);
    void riskFree(double r_);
    void spot(double S_);
    void strike(double K_);
    void carry(double b_);
};

#endif // OPTION_HPP
