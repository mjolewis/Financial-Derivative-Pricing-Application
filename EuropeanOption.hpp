/**********************************************************************************************************************
 * Black-Scholes pricing application for European (plain) Options
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include <vector>

#include "Mesher.hpp"
#include "Matrix.hpp"
#include "Output.hpp"

template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
class EuropeanOption : public Mesher_, public Matrix_, public RNG_, public Output_ {

private:
    // Required option data
    double T;                                    // Expiry time/maturity. E.g. T = 1 means one year
    double sig;                                  // Volatility
    double r;                                    // Risk-free interest rate
    double S;                                    // Spot price
    double K;                                    // Strike price
    double b;                                    // Cost of carry; b = r for Black-Scholes equity option model

    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    static bool putCallParity(double C, double P, double T_, double K_, double r_, double S);

    // Helper function to price the option
    std::vector<std::vector<double>> price(double T_, double sig_, double r_, double S_, double K_, double b_) const;

public:
    // Constructors and destructors
    EuropeanOption();
    EuropeanOption(const EuropeanOption& source);
    EuropeanOption(double T_, double sig_, double r_, double S_, double K_, double b_);
    virtual ~EuropeanOption();

    // Operator overloading
    EuropeanOption& operator=(const EuropeanOption& source);

    // European Option Pricing Formulae
    std::vector<std::vector<double>> price() const;
    std::vector<std::vector<double>> price(const std::vector<std::vector<double> >& matrix) const;
    void price(double h, double start, double stop, double step, const std::string& property) const;

    // Mechanism to calculate the call (or put) price for a corresponding put (or call) price
    double putCallParity(double optionPrice, const std::string& optType_) const;
    // Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
    bool putCallParity(double callPrice, double putPrice) const;

    // Exact solutions for option sensitivities (Greeks)
    std::vector<std::vector<double>> delta() const;
    std::vector<std::vector<double>> delta(double T_, double sig_, double r_, double S_, double K_, double b_) const;
    std::vector<std::vector<double>> delta(const std::vector<std::vector<double>>& matrix) const;
    double gamma() const;
    double gamma(double T_, double sig_, double r_, double S_, double K_, double b_) const;
    std::vector<double> gamma(const std::vector<std::vector<double>>& matrix) const;

    // European Greeks using Finite difference methods
    std::vector<std::vector<double>> delta(double h) const;
    std::vector<std::vector<double>> delta(double h, double T_, double sig_, double r_, double S_, double K_, double b_) const;
    std::vector<std::vector<double>> delta(double h, const std::vector<std::vector<double>>& matrix) const;
    double gamma(double h) const;
    std::vector<double>gamma(double h, const std::vector<std::vector<double>>& matrix) const;
    double gamma(double h, const std::vector<double>& option) const;

    // Accessors
    double expiry() const;
    double vol() const;
    double riskFree() const;
    double spot() const;
    double strike() const;
    double carry() const;

    // Mutators
    void setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_);
    void expiry(double T_);
    void vol(double sig_);
    void riskFree(double r_);
    void spot(double S_);
    void strike(double K_);
    void carry(double b_);
};

#ifndef EUROPEANOPTION_CPP
#include "EuropeanOption.cpp"

#endif // EUROPEANOPTION_CPP
#endif // EUROPEANOPTION_HPP
