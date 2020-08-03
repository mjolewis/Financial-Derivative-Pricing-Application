/**********************************************************************************************************************
 * European equity option
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "string"
#include "boost/tuple/tuple.hpp"

#include "Instrument.hpp"

class Option : public Instrument {
private:

    // Required option data
    double T;                           // Expiry time/maturity. E.g. T = 1 means one year
    double sig;                         // Volatility
    double r;                           // Risk-free interest rate
    double S;                           // Spot price
    double K;                           // Strike price
    double b;                           // Cost of carry; b = r for Black-Scholes equity option model
    std::string optType;                // Call or Put
    std::string optFlavor;              // European, American
    std::string uName;                  // Underlying

public:

    // Constructors and Destructors
    Option();
    Option(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optType_, std::string& optFlavor_, std::string& uName_);
    Option(const Option &source);
    virtual ~Option();

    // Operator overloading
    Option &operator=(const Option &source);

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
};

#endif // EUROPEANOPTION_HPP
