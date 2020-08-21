/**********************************************************************************************************************
 * Black-Scholes pricing application. Provides access to the core Option pricing and sensitivity engine
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_HPP
#define PRICER_HPP

#include <vector>
#include <boost/tuple/tuple_io.hpp>

#include "Mesher.hpp"
#include "Matrix.hpp"
#include "Output.hpp"
#include "Option.hpp"

template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
class Pricer : public Mesher_, public Matrix_, public RNG_, public Output_ {

private:

public:
    // Constructors and destructors
    Pricer();
    Pricer(const Option& option_);
    Pricer(const Pricer& source);
    virtual ~Pricer();

    // Operator overloading
    Pricer& operator=(const Pricer& source);

    // American Option Pricing Formulae
    std::vector<std::vector<double>> priceAmerican(const std::vector<std::vector<double> >& matrix) const;
    std::vector<std::vector<double>> priceAmerican(double T, double sig, double r, double S, double K, double b) const;
    void priceAmerican(double h, double start, double stop, double step, const Option& option, const std::string& property) const;

    // European Option Pricing Formulae
    std::vector<std::vector<double>> priceEuropean(const std::vector<std::vector<double> >& matrix) const;
    std::vector<std::vector<double>> priceEuropean(double T, double sig, double r, double S, double K, double b) const;
    void priceEuropean(double h, double start, double stop, double step, const Option& option, const std::string& property) const;

    // Exact solutions for option sensitivities (Greeks)
    std::vector<std::vector<double>> delta(double T, double sig, double r, double S, double K, double b) const;
    std::vector<std::vector<double>> delta(const std::vector<std::vector<double>>& matrix) const;
    double gamma(double T, double sig, double r, double S, double K, double b) const;
    std::vector<double> gamma(const std::vector<std::vector<double>>& matrix) const;
    double vega(double T, double sig, double r, double S, double K, double b) const;

    // American Greeks using Finite difference methods
    std::vector<std::vector<double>> deltaAmerican(double h, double T, double sig, double r, double S, double K, double b) const;
    std::vector<std::vector<double>> deltaAmerican(double h, const std::vector<double>& option) const;
    std::vector<std::vector<double>> deltaAmerican(double h, const std::vector<std::vector<double>>& matrix) const;
    double gammaAmerican(double h, const std::vector<double>& option) const;
    std::vector<double>gammaAmerican(double h, const std::vector<std::vector<double>>& matrix) const;

    // European Greeks using Finite difference methods
    std::vector<std::vector<double>> deltaEuropean(double h, double T, double sig, double r, double S, double K, double b) const;
    std::vector<std::vector<double>> deltaEuropean(double h, const std::vector<double>& option) const;
    std::vector<std::vector<double>> deltaEuropean(double h, const std::vector<std::vector<double>>& matrix) const;
    double gammaEuropean(double h, const std::vector<double>& option) const;
    std::vector<double>gammaEuropean(double h, const std::vector<std::vector<double>>& matrix) const;
};

#ifndef PRICER_CPP
#include "Pricer.cpp"

#endif // PRICER_CPP
#endif // PRICER_HPP
