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
template<typename Input_, typename RNG_, typename Instrument_>
Pricer<Input_, RNG_, Instrument_>::Pricer() : Input_(), RNG_(), Instrument_() {}

/**
 * Initialize a new Pricer object with the specified parameters
 * @param optionData_ A {@link boost::tuple} containing values to initialize core option data (e.g expiry,
 * volatility, risk-free rate, spot price, strike price, option type)
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Input_, typename RNG_, typename Instrument_>
Pricer<Input_, RNG_, Instrument_>::Pricer(const OptionData &optionData_) : Input_(), RNG_(), Instrument_(), optionData(optionData_) {}

/**
 * Initialize a deep copy of the specified source
 * @param source A Pricer that will be deeply copied
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Input_, typename RNG_, typename Instrument_>
Pricer<Input_, RNG_, Instrument_>::Pricer(const Pricer &source) : Input_(), RNG_(), Instrument_(), optionData(source.optionData) {}

/**
 * Destroy's this Pricer
 */
template<typename Input_, typename RNG_, typename Instrument_>
Pricer<Input_, RNG_, Instrument_>::~Pricer() {}

/**
 * Create a deep copy of the source Pricer
 * @param source A Pricer that will be deeply copied
 * @return A reference to this Pricer
 */
template<typename Input_, typename RNG_, typename Instrument_>
Pricer<Input_, RNG_, Instrument_> &Pricer<Input_, RNG_, Instrument_>::operator=
        (const Pricer<Input_, RNG_, Instrument_> &source) {
    // Avoid self assign
    if (this == &source) { return *this; }

    optionData = source.optionData;

    return *this;
}

/**
 * Accessor function that returns the option data
 * @return A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K, optType)
 */
template<typename Input_, typename RNG_, typename Instrument_>
const OptionData &Pricer<Input_, RNG_, Instrument_>::getOptionData() const { return optionData; }


/**
 * Leverages Input.cpp to provide a console UI, allowing the user to dynamically input option data
 * @tparam Input_
 * @tparam RNG_
 * @tparam Instrument_
 */
template<typename Input_, typename RNG_, typename Instrument_>
void Pricer<Input_, RNG_, Instrument_>::getOptionInput() { optionData = Input_::getOptionInput();}

/**
 * Accessor function that returns the option prices
 * @return A {@link std::vector} of option prices
 */
template<typename Input_, typename RNG_, typename Instrument_>
std::vector<double> Pricer<Input_, RNG_, Instrument_>::getOptionPrices() const { return optionPrices; }

/**
 * The core pricing engine that uses the Black-Scholes formula to price various types of options
 * @return The price of the option
 */
template<typename Input_, typename RNG_, typename Instrument_>
double Pricer<Input_, RNG_, Instrument_>::price() {

    // Required option data
    double T = optionData.get<0>();                          // Expiry time/maturity. E.g. T = 1 means one year
    double sig = optionData.get<1>();                        // Volatility
    double r = optionData.get<2>();                          // Risk-free interest rate
    double S = optionData.get<3>();                          // Spot price
    double K = optionData.get<4>();                          // Strike price
    double b = optionData.get<5>();                          // Cost of carry
    std::string optType = optionData.get<6>();               // Put or Call
    std::string optFlavor = optionData.get<7>();             // European or American

    if (optType == "Call") {
        optionPrice = callPrice(T, sig, r, S, K, b, optFlavor);
    } else if (optType == "Put") {
        optionPrice = putPrice(T, sig, r, S, K, b, optFlavor);
    }
    return optionPrice;
}

/**
 * Mutator function that assigns the parameter to this objects optionData member
 * @param optionData_ A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K,
 * optType)
 */
template<typename Input_, typename RNG_, typename Instrument_>
void Pricer<Input_, RNG_, Instrument_>::setOptionData(const OptionData &optionData_) {
    optionData = optionData_;
}

// Calculates the call price using the Black-Scholes formula
template<typename Input_, typename RNG_, typename Instrument_>
double Pricer<Input_, RNG_, Instrument_>::callPrice(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optFlavor_) {

    if (optFlavor_ == "European") {
        double tmp = sig_ * sqrt(T_);

        double d1 = (log(S_/K_) + (b_ + (sig_ * sig_) * 0.5) * T_ ) / tmp;
        double d2 = d1 - tmp;

        double N1 = RNG_::CDF(d1);
        double N2 = RNG_::CDF(d2);

        optionPrice = (S_ * exp((b_ - r_) * T_) * N1) - (K_ * exp(-r_ * T_) * N2);
    } else if (optFlavor_ == "American") {
        //todo
    }

    return optionPrice;
}


// Calculates the put price using the Black-Scholes formula
template<typename Input_, typename RNG_, typename Instrument_>
double Pricer<Input_, RNG_, Instrument_>::putPrice(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optFlavor_) {

    if (optFlavor_ == "European") {
        double tmp = sig_ * sqrt(T_);

        double d1 = (log(S_/K_) + (b_ + (sig_ * sig_) * 0.5) * T_ ) / tmp;
        double d2 = d1 - tmp;

        double N1 = RNG_::CDF(-d1);
        double N2 = RNG_::CDF(-d2);

        optionPrice = (K_ * exp(-r_ * T_) * N2) - (S_ * exp((b_ - r_) * T_) * N1);
    } else if (optFlavor_ == "American") {
        //todo
    }

    return optionPrice;
}

#endif