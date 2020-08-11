/**********************************************************************************************************************
 * European equity option
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include <string>
#include <cmath>
#include <boost/tuple/tuple.hpp>

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
    std::string optType;                         // Call or Put
    std::string optFlavor;                       // European, American
    std::string uName;                           // Underlying

    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    static bool putCallParity(double C, double P, double T_, double K, double r_, double S);

public:

    // Constructors and Destructors
    Option();
    Option(double T_, double sig_, double r_, double S_, double K_, double b_,
            const std::string& optType_, const std::string& optFlavor_, const std::string& uName_);
    Option(const Option &source);
    virtual ~Option();

    // Operator overloading
    Option &operator=(const Option &source);

    // Mechanism to calculate the call (or put) price for a corresponding put (or call) price
    double putCallParity(double optionPrice, const std::string& optType_ = "Call") const;

    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    bool putCallParity(double callPrice, double putPrice) const;

    // Getters
    double expiry() const;
    double vol() const;
    double riskFree() const;
    double spot() const;
    double strike() const;
    double carry() const;
    const std::string& type() const;
    const std::string& flavor() const;
    const std::string& underlying() const;

    // Setters
    void setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_, const std::string& optType_,
                               const std::string& optFlavor_, const std::string& uName_);
    void expiry(double T_);
    void vol(double sig_);
    void riskFree(double r_);
    void spot(double S_);
    void strike(double K_);
    void carry(double b_);
    void type(const std::string& optType_);
    void flavor(const std::string& optFlavor_);
    void underlying(const std::string& uName_);
};

#endif // EUROPEANOPTION_HPP
