/**********************************************************************************************************************
 * Function definitions for Pricer.cpp
 *
 * A financial derivatives pricing engine that employs the Black-Scholes formula with exact methods.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_CPP
#define PRICER_CPP

#include "Pricer.hpp"

#include <boost/tuple/tuple_io.hpp>
#include <iostream>
#include "Input.hpp"

/**
 * Initialize a new Pricer object
 * @throws OutOfMemoryException Indicates insufficient memory for this new Pricer object
 */
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer() : Input_(), RNG_(), Mesher_() {}

/**
 * Initialize a new Pricer object with the specified parameters
 * @param optionData_ A {@link boost::tuple} containing values to initialize core option data (e.g expiry,
 * volatility, risk-free rate, spot price, strike price, option type)
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer(const OptionData &optionData_) : Input_(), RNG_(), Mesher_(), optionData(optionData_) {}

/**
 * Initialize a deep copy of the specified source
 * @param source A Pricer that will be deeply copied
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::Pricer(const Pricer &source) : Input_(), RNG_(), Mesher_(), optionData(source.optionData) {}

/**
 * Destroy's this Pricer
 */
template<typename Input_, typename RNG_, typename Mesher_>
Pricer<Input_, RNG_, Mesher_>::~Pricer() {}

/**
 * Create a deep copy of the source Pricer
 * @param source A Pricer that will be deeply copied
 * @return A reference to this Pricer
 */
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

/**
 * Accessor function that returns the option data
 * @return A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K, optType)
 */
template<typename Input_, typename RNG_, typename Mesher_>
const OptionData &Pricer<Input_, RNG_, Mesher_>::getOptionData() const { return optionData; }


/**
 * Leverages Input.cpp to provide a console UI, allowing the user to dynamically input option data
 */
template<typename Input_, typename RNG_, typename Mesher_>
void Pricer<Input_, RNG_, Mesher_>::getOptionInput() { optionData = Input_::getOptionInput();}

/**
 * Accessor function that returns the option prices
 * @return A {@link std::vector} of option prices
 */
template<typename Input_, typename RNG_, typename Mesher_>
std::vector<double> Pricer<Input_, RNG_, Mesher_>::getOptionPrices() const { return optionPrices; }

/**
 * The core pricing engine that uses the Black-Scholes formula to calculate an exact solution. Note that this version
 * gets the option parameters from the user by providing a console UI
 * @return The price of the option
 */
template<typename Input_, typename RNG_, typename Mesher_>
double Pricer<Input_, RNG_, Mesher_>::price() {

    getOptionInput();                                        // Get option data from the user

    // Required option data
    double T = optionData.get<0>();                          // Expiry time/maturity. E.g. T = 1 means one year
    double sig = optionData.get<1>();                        // Volatility
    double r = optionData.get<2>();                          // Risk-free interest rate
    double S = optionData.get<3>();                          // Spot price
    double K = optionData.get<4>();                          // Strike price
    double b = optionData.get<5>();                          // Cost of carry
    std::string optType = optionData.get<6>();               // Put or Call
    std::string optFlavor = optionData.get<7>();             // European or American

    optionPrice = price(T, sig, r, S, K, b, optType, optFlavor);
    return optionPrice;
}

/**
 * The core pricing engine that uses the Black-Scholes formula to price various types of options
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
double Pricer<Input_, RNG_, Mesher_>::price(double T_, double sig_,
                                            double r_, double S_, double K_, double b_,
                                            std::string& optType_, std::string& optFlavor_) {

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_/K_) + (b_ + (sig_ * sig_) * 0.5) * T_ ) / tmp;
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

/**
 * Mutator function that assigns the parameter to this objects optionData member
 * @param optionData_ A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K,
 * optType)
 */
template<typename Input_, typename RNG_, typename Mesher_>
void Pricer<Input_, RNG_, Mesher_>::setOptionData(const OptionData &optionData_) {
    optionData = optionData_;
}

#endif