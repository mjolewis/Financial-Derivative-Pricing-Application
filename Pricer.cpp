/**********************************************************************************************************************
 * Function definitions for Pricer.cpp
 *
 * A financial derivatives pricing and sensitivity engine that employs the Black-Scholes formula
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_CPP
#define PRICER_CPP

#include "Pricer.hpp"

#include <boost/tuple/tuple_io.hpp>
#include <iostream>
#include "Input.hpp"

// Initialize a new Pricer
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer() : Input_(), RNG_(), Mesher_() {}

// Initialize a new Pricer where optionData is a boost::tuple with expiry, vol, risk-free, spot, strike, option type
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer(const OptionData &optionData_)
        : Input_(), RNG_(), Mesher_(), optionData(optionData_) {}

// Initialize a deep copy of the source
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer(const Pricer &source)
        : Input_(), RNG_(), Mesher_(), optionData(source.optionData) {}

// Destroy this Pricer
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::~Pricer() {}

// Create a deep copy of the source
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_> &Pricer<Input_, RNG_, Mesher_>::operator=
        (const Pricer<Input_, RNG_, Mesher_> &source) {
    // Avoid self assign
    if (this == &source) { return *this; }

    // Call base class assignment
    Input_::operator=(source);
    RNG_::operator=(source);
    Mesher_::operator=(source);

    optionData = source.optionData;

    return *this;
}

/* ********************************************************************************************************************
 * Getters and Setters
 *********************************************************************************************************************/

// optionData is a boost::tuple
template<typename Input_, typename RNG_, typename Mesher_>
const OptionData &Pricer<Input_, RNG_, Mesher_>::getOptionData() const { return optionData; }

// Mutator function that assigns the parameter to this objects optionData member(e.g. Expiry, sig, r, S, K,
template<typename Input_, typename RNG_, typename Mesher_>
void Pricer<Input_, RNG_, Mesher_>::setOptionData(const OptionData &optionData_) { optionData = optionData_; }

/* ********************************************************************************************************************
 * Option sensitivities (Greeks)
 *********************************************************************************************************************/

/**
 *
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @param optType
 * @return The call delta if optType is a call. Otherwise the put delta
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::delta(double T_, double sig_, double r_,
                                            double S_, double K_, double b_, const std::string &optType) const {

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;

    if (optType == "Put" || optType == "put") { return exp((b_ - r_) * T_) * (RNG_::CDF(d1) - 1.0); }

    // optType is a call
    return exp((b_ - r_) * T_) * RNG_::CDF(d1);
}

/**
 *
 * @return A call delta matrix (default) or a put delta matrix
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::delta(const std::vector<std::vector<double> > &matrix, const std::string &optType_) {

    std::vector<std::vector<double> > deltaPrices;              // A container of delta approximations

    for (int i = 0; i < matrix.size(); ++i) {

        // Calculate the call or put delta
        deltaPrice = delta(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], matrix[i][4], matrix[i][5],
                           optType_);

        // Add deltaPrice to the output matrix
        deltaPrices.push_back({deltaPrice});
    }
    return deltaPrices;
}

/**
 * Approximate option delta using the divided differences method
 * @param h
 * @param option An option with T, sig, r, S, K, b, optType, and optFlavor
 * @return The delta call or delta put, which depends on the type of option provided
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::delta(double h, const std::string &optType, const std::string& optFlavor,
        const std::vector<double>& option) {

    // Input for divided differences numerator
    double S1 = option[3] + h;
    double S2 = option[3] - h;

    // Placeholders for final numerator values
    double LHS = price(option[0], option[1], option[2], S1, option[4], option[5], optType, optFlavor);
    double RHS = price(option[0], option[1], option[2], S2, option[4], option[5], optType, optFlavor);

    // Divided differences method
    deltaPrice = (LHS - RHS) / (2 * h);

    return deltaPrice;
}

template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>> Pricer<Input_, RNG_, Mesher_>::delta(double h, const std::string &optType,
        const std::string& optFlavor, const std::vector<std::vector<double> > &matrix) {

    // Container for divided differences results
    std::vector<std::vector<double>> deltaPrices;

    for (const auto & i : matrix) {
        deltaPrices.push_back({delta(h, optType, optFlavor, i)});
    }

    return deltaPrices;
}

/**
 * Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @return The rate of change with respect to the input parameters
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::gamma(double T_, double sig_, double r_, double S_, double K_, double b_) const {
    double tmp = sig_ * sqrt(T_);

    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;

    double n1 = RNG_::PDF(d1);

    return (n1 * exp((b_ - r_) * T_)) / (S_ * tmp);
}

/**
 * Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @return A Gamma matrix
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::gamma(const std::vector<std::vector<double> > &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammaMatrix;
    double temp;

    for (int i = 0; i < matrix.size(); ++i) {

        // Calculate gamma
        temp = gamma(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], matrix[i][4], matrix[i][5]);

        // Add gamma to the output matrix
        gammaMatrix.push_back({temp});
    }
    return gammaMatrix;
}

/**
 * Measures an option's sensitivity to implied volatility. It is the change in the option price for a one-point change
 * in implied volatility
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @return The rate of change in the option price with respect to volatility
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::vega(double T_, double sig_, double r_, double S_, double K_, double b_) const {
    double tmp = sig_ * sqrt(T_);

    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;

    return (S_ * exp((b_ - r_) * T_) * RNG_::PDF(d1) * sqrt(T_));
}

/* ********************************************************************************************************************
 * Core pricing functions
 *********************************************************************************************************************/

/**
 * The core pricing engine that uses the Black-Scholes formula to calculate an exact solution. Note that this version
 * provides a console interface to dynamically get option data
 * @return The option price
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::price() {

    optionData = Input_::getOptionInput();                 // Provide a console interface to dynamically get option data

    // Required option data
    double T = optionData.get<0>();                        // Expiry time/maturity. E.g. T = 1 means one year
    double sig = optionData.get<1>();                      // Volatility
    double r = optionData.get<2>();                        // Risk-free interest rate
    double S = optionData.get<3>();                        // Spot price
    double K = optionData.get<4>();                        // Strike price
    double b = optionData.get<5>();                        // Cost of carry
    std::string optType = optionData.get<6>();             // Put or Call
    std::string optFlavor = optionData.get<7>();           // European or American

    optionPrice = price(T, sig, r, S, K, b, optType, optFlavor);
    return optionPrice;
}

/**
 * Receives a matrix of options and prices each of of them
 * @param matrix Option parameters
 * @return A matrix of option prices
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double> > Pricer<Input_, RNG_, Mesher_>::price(
        const std::vector<std::vector<double> > &matrix, const std::string &optType_, const std::string &optFlavor_) {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > optionPrices;

    for (int i = 0; i < matrix.size(); ++i) {

        // Price the option
        price(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], matrix[i][4], matrix[i][5], optType_, optFlavor_);

        // Store the price
        optionPrices.push_back({optionPrice});
    }
    return optionPrices;
}

/**
 * The core pricing engine that uses the Black-Scholes formula
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @param optType_ Put or Call
 * @param optFlavor_ European or American
 * @return The price of the option
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::price(double T_, double sig_, double r_, double S_, double K_, double b_,
                                            const std::string &optType_, const std::string &optFlavor_) {

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;
    double d2 = d1 - tmp;

    if (optType_ == "Call" && optFlavor_ == "European") {

        double N1 = RNG_::CDF(d1);
        double N2 = RNG_::CDF(d2);
        optionPrice = (S_ * exp((b_ - r_) * T_) * N1) - (K_ * exp(-r_ * T_) * N2);

    } else if (optType_ == "Put" && optFlavor_ == "European") {

        double N1 = RNG_::CDF(-d1);
        double N2 = RNG_::CDF(-d2);
        optionPrice = (K_ * exp(-r_ * T_) * N2) - (S_ * exp((b_ - r_) * T_) * N1);

    } else if (optType_ == "Call" && optFlavor_ == "American") {
        //todo
    } else {
        //todo
    }

    return optionPrice;
}

#endif