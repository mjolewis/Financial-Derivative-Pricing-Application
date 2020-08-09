/**********************************************************************************************************************
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
 * Calculate closed form solution for Delta
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
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
double Pricer<Input_, RNG_, Mesher_>::delta(double T_, double sig_, double r_, double S_,
                                            double K_, double b_, const std::string &optType) const {

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;

    if (optType == "Put" || optType == "put") { return exp((b_ - r_) * T_) * (RNG_::CDF(d1) - 1.0); }

    // optType is a call
    return exp((b_ - r_) * T_) * RNG_::CDF(d1);
}

/**
 * Calculate closed form solution for Delta
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @param matrix A matrix option parameters where each row has T, sig, r, S, K, b
 * @param optType_ Call or Put
 * @return A call delta matrix (default) or a put delta matrix
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::delta(const std::vector<std::vector<double> > &matrix, const std::string &optType_) const {

    std::vector<std::vector<double> > deltas;              // A container of delta approximations

    // Calculate exact deltas and store in the output matrix
    for (const auto & i : matrix) {
        deltas.push_back({delta(i[0], i[1], i[2], i[3], i[4], i[5], optType_)});
    }
    return deltas;
}

/**
 * Approximate option delta using the divided differences method
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @param h
 * @param optType An option with T, sig, r, S, K, b, optType, and optFlavor
 * @param optFlavor European or American
 * @return The delta call or delta put, which depends on the type of option provided
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::delta(double h, const std::vector<double>& option,
        const std::string &optType, const std::string& optFlavor) const {

    // Input for divided differences numerator
    double S1 = option[3] + h;
    double S2 = option[3] - h;

    // Placeholders for final numerator values
    double LHS = price(option[0], option[1], option[2], S1, option[4], option[5], optType, optFlavor);
    double RHS = price(option[0], option[1], option[2], S2, option[4], option[5], optType, optFlavor);

    // Divided differences method
    return (LHS - RHS) / (2 * h);
}

/**
 * Approximate option delta using the divided differences method
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @param h
 * @param optType Call or Put
 * @param optFlavor European or American
 * @param matrix A matrix option parameters where each row has T, sig, r, S, K, b
 * @return
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::delta(double h, const std::vector<std::vector<double> > &matrix,
        const std::string &optType, const std::string& optFlavor) const {

    // Container for divided differences results
    std::vector<std::vector<double>> deltaPrices;

    for (const auto & i : matrix) {
        deltaPrices.push_back({delta(h, i, optType, optFlavor)});
    }

    return deltaPrices;
}

/**
 * Calculate closed form solution for Gamma
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
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
 * Calculate closed form solution for Gamma
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @param matrix A matrix of option parameters (e.g. T, sig, r, S, K, b)
 * @return A matrix of closed form solutions for Gamma (one solution for each row of options in the input matrix)
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::gamma(const std::vector<std::vector<double> > &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammaMatrix;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto & i : matrix) {
        gammaMatrix.push_back({gamma(i[0], i[1], i[2], i[3], i[4], i[5])});
    }
    return gammaMatrix;
}

/**
 * Approximate Gamma using the divided differences method
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @param h Smaller values of h produce better approximations but we need to avoid round-off errors
 * @param option A call or put option used to approximate gamma
 * @return An approximation of Gamma for the given option
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::gamma(double h, const std::vector<double> &option) const {

    // Input for divided differences numerator
    double S1 = price(option[0], option[1], option[2], option[3] + h, option[4], option[5]);
    double S2 = 2 * price(option[0], option[1], option[2], option[3], option[4], option[5]);
    double S3 = price(option[0], option[1], option[2], option[3] - h, option[4], option[5]);

    // Divided differences method
    return (S1 - S2 + S3) / (h * h);
}

/**
 * Approximate Gamma using the divided differences method
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @return A matrix of Gamma approximations (one solution for each row of options in the input matrix)
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double>>
Pricer<Input_, RNG_, Mesher_>::gamma(double h, const std::vector<std::vector<double>> &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammaMatrix;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto & i : matrix) {
        gammaMatrix.push_back({gamma(h, i)});
    }

    return gammaMatrix;
}

/**
 * Calculate closed form solution for Vega
 * @Note Measures option sensitivity to implied vol (e.g. change in the option price per point change in implied vol)
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

    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / (sig_ * sqrt(T_));

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

    return price(T, sig, r, S, K, b, optType, optFlavor);
}

/**
 * Receives a matrix of options and prices each of of them
 * @param matrix Option parameters
 * @return A matrix of option prices
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<std::vector<double> >
Pricer<Input_, RNG_, Mesher_>::price( const std::vector<std::vector<double> > &matrix,
        const std::string &optType_, const std::string &optFlavor_) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > optionPrices;

    for (const auto & row : matrix) {
        // Store the price
        optionPrices.push_back({price(row[0], row[1], row[2], row[3], row[4], row[5], optType_, optFlavor_)});
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
 * @return The price of the option. Otherwise -1 for invalid input
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::price(double T_, double sig_, double r_, double S_, double K_, double b_,
                                            const std::string &optType_, const std::string &optFlavor_) const {

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;
    double d2 = d1 - tmp;

    if (optType_ == "Call" && optFlavor_ == "European") {

        double N1 = RNG_::CDF(d1);
        double N2 = RNG_::CDF(d2);
        return (S_ * exp((b_ - r_) * T_) * N1) - (K_ * exp(-r_ * T_) * N2);

    } else if (optType_ == "Put" && optFlavor_ == "European") {

        double N1 = RNG_::CDF(-d1);
        double N2 = RNG_::CDF(-d2);
        return (K_ * exp(-r_ * T_) * N2) - (S_ * exp((b_ - r_) * T_) * N1);

    } else if (optType_ == "Call" && optFlavor_ == "American") {
        //todo
    } else {
        //todo
    }

    return -1;                                             // Indicates invalid input
}

#endif