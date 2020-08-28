/**********************************************************************************************************************
 * Black-Scholes pricing application. Provides access to the core Option pricing and sensitivity engine
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef EUROPEANOPTION_CPP
#define EUROPEANOPTION_CPP

#include "EuropeanOption.hpp"
#include "Mesher.hpp"
#include "Matrix.hpp"
#include "Output.hpp"
#include "RNG.hpp"

/**
 * Initialize a new European Option with default parameters provided by the C++ for Financial Engineering course
 * through QuantNet and Baruch College
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @throws OutOfMemoryError Indicates insufficient memory for this new EuropeanOption
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::EuropeanOption() : Mesher_(), Matrix_(), RNG_(), Output_(), T(0.25),
sig(0.30), r(0.08), S(60), K(65), b(0.08) {}

/**
 * Initialize a new European Option, whose data members will be a deep copy of the source
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source whose data members will be deeply copied into this EuropeanOption
 * @throws OutOfMemoryError Indicates insufficient memory for this new EuropeanOption
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::EuropeanOption(const EuropeanOption<Mesher_, Matrix_, RNG_, Output_>
        &source) : Mesher_(), Matrix_(), RNG_(), Output_(), T(source.T), sig(source.sig), r(source.r), S(source.S),
        K(source.K), b(source.b) {}

/**
 * Initialize a new EuropeanOption whose members are a deep copy of the source
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source A EuropeanOption whose data members will be deeply copied into this new EuropeanOption
 * @throws OutOfMemoryError Indicates insufficient memory for this new EuropeanOption
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::EuropeanOption(double T_, double sig_, double r_, double S_, double K_,
        double b_) : Mesher_(), Matrix_(), RNG_(), Output_(), T(T_), sig(sig_), r(r_), S(S_), K(K_), b(b_) {}

/**
 * Destroy this EuropeanOption
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::~EuropeanOption() {}

/* ********************************************************************************************************************
 * Operator Overloading
 *********************************************************************************************************************/

/**
 * Deeply copy the source data members into this EuropeanOption
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source A EuropeanOption whose data members will be deeply copied into this new EuropeanOption
 * @return A EuropeanOption whose data members are a deep copy of the source data members
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_> &EuropeanOption<Mesher_, Matrix_, RNG_, Output_>
        ::operator=(const EuropeanOption<Mesher_, Matrix_, RNG_, Output_> &source) {

    // Avoid self assign
    if (this == &source) { return *this; }

    // Call base class assignment
    Mesher_::operator=(source);
    Matrix_::operator=(source);
    RNG_::operator=(source);
    Output_::operator=(source);

    return *this;
}

/* ********************************************************************************************************************
 * Exact Solutions for Option sensitivities (Greeks)
 *********************************************************************************************************************/

/**
 * Calculate closed form solution for Call and Put Delta of this European Option
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return A matrix of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta() const {
    return delta(T, sig, r, S, K, b);
}

/**
 * Calculate closed form solution for Call and Put Delta using the specified parameters
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-free rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of carry
 * @return A matrix of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta(double T_, double sig_,
        double r_, double S_, double K_, double b_) {

    std::vector<std::vector<double>> deltas;

    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / (sig_ * sqrt(T_));

    // Add call delta then put delta
    double callDelta = exp((b_ - r_) * T_) * RNG_::CDF(d1);
    double putDelta = exp((b_ - r_) * T_) * (RNG_::CDF(d1) - 1.0);

    deltas.push_back({callDelta, putDelta});

    return deltas;
}

/**
 * Calculate closed form solution for Delta
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param matrix A matrix of option parameters where each row has T, sig, r, S, K, b
 * @return A matrix of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta(const std::vector<std::vector<double> > &matrix) {

    std::vector<std::vector<double> > deltas;

    for (const auto &i : matrix) {
        deltas.push_back(delta(i[0], i[1], i[2], i[3], i[4], i[5])[0]);      // Each row contains Call and Put Deltas
    }
    return deltas;
}

/**
 * Calculate closed form solution of Gamma for this European Option
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Gamma of this European Option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma() const {
    return gamma(T, sig, r, S, K, b);
}

/**
 * Calculate closed form solution of Gamma for the specified parameters
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @return The rate of change with respect to the input parameters
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma(double T_, double sig_, double r_, double S_, double K_,
        double b_) {
    double tmp = sig_ * sqrt(T_);

    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;

    double n1 = RNG_::PDF(d1);

    return (n1 * exp((b_ - r_) * T_)) / (S_ * tmp);
}

/**
 * Calculate closed form solution for Gamma
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param matrix A matrix of option parameters (e.g. T, sig, r, S, K, b)
 * @return A matrix of closed form solutions for Gamma (one solution for each row of options in the input matrix)
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma(const std::vector<std::vector<double> > &matrix) {

    // Create a new container for each new matrix
    std::vector<double> gammas;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto &i : matrix) {
        gammas.push_back(gamma(i[0], i[1], i[2], i[3], i[4], i[5]));
    }
    return gammas;
}

/* ********************************************************************************************************************
 * FDM for Option sensitivities (Greeks)
 *********************************************************************************************************************/

/**
 * FDM to approximate option this options delta using divided differences
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @return A vector of Call and Put Delta Approximations
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta(double h) const {
    return delta(h, T, sig, r, S, K, b);
}

/**
 * FDM to approximate option delta using divided differences
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @return A vector of Call and Put Delta Approximations
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta(double h, double T_,
        double sig_, double r_, double S_, double K_, double b_) {

    // Call and Put Deltas
    std::vector<std::vector<double>> deltas;

    // Placeholders for final numerator values
    std::vector<double> LHS = price(T_, sig_, r_, S_ + h, K_, b_)[0];
    std::vector<double> RHS = price(T_, sig_, r_, S_ - h, K_, b_)[0];

    // Divided differences method
    double callDelta = (LHS[0] - RHS[0]) / (2 * h);              // Call prices
    double putDelta = (LHS[1] - RHS[1]) / (2 * h);               // Put prices

    deltas.push_back({callDelta, putDelta});

    return deltas;
}

/**
 * FDM to approximate option delta using divided differences
 * @note Delta is the change in the option’s price or premium due to the change in the Underlying futures price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @param matrix A matrix option parameters where each row has T, sig, r, S, K, b
 * @return The delta call or delta put approximation, which depends on the type of option provided
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::delta(double h, const std::vector<std::vector<double> > &matrix) {

    // Container for divided differences results
    std::vector<std::vector<double>> deltaPrices;

    for (const auto &row : matrix) {
        deltaPrices.push_back(delta(h, row[0], row[1], row[2], row[3], row[4], row[5])[0]);
    }

    return deltaPrices;
}

/**
 * FDM to approximate this options Gamma using divided differences
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @param option A call or put option used to approximate gamma
 * @return An approximation of Gamma for the given option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma(double h) const {
    // Input for divided differences numerator
    double S1 = price(T, sig, r, S + h, K, b)[0][0];
    double S2 = 2 * price(T, sig, r, S, K, b)[0][0];
    double S3 = price(T, sig, r, S - h, K, b)[0][0];

    // Divided differences method
    return (S1 - S2 + S3) / (h * h);
}

/**
 * FDM to approximate Gamma using divided differences
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @param option A call or put option used to approximate gamma
 * @return An approximation of Gamma for the given option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma(double h, const std::vector<double> &option) {

    // Input for divided differences numerator
    double S1 = (price(option[0], option[1], option[2], option[3] + h, option[4], option[5])[0][0]);
    double S2 = 2 * (price(option[0], option[1], option[2], option[3], option[4], option[5])[0][0]);
    double S3 = (price(option[0], option[1], option[2], option[3] - h, option[4], option[5])[0][0]);

    // Divided differences method
    return (S1 - S2 + S3) / (h * h);
}

/**
 * FDM to approximate Gamma using divided differences
 * @note Gamma is the rate of change in an options delta per one point move in the underlying asset's price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return A matrix of Gamma approximations (one solution for each row of options in the input matrix)
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double>
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::gamma(double h, const std::vector<std::vector<double>> &matrix) {

    // Create a new container for each new matrix
    std::vector<double> gammas;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto &i : matrix) {
        gammas.push_back(gamma(h, i));
    }

    return gammas;
}

/* ********************************************************************************************************************
 * Core pricing functions - European Options
 *********************************************************************************************************************/

/**
 * The core pricing engine that uses the Black-Scholes formula
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param h Difference parameter
 * @param start Start point of interval
 * @param stop End point of interval
 * @param step The step size within the interval
 * @param property The option parameter which will be monotonically increased by the Mesher
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::price(double h, double start, double stop, double step,
        const std::string& property) const {

    std::vector<double> mesh = Mesher_::xarr(start, stop, step);     // Generate the mesh points for the matrix

    std::vector<std::vector<double>> matrix = Matrix_::matrix(mesh, property, T, sig, r, S, K, b);

    // Create and fill containers with option data
    std::vector<std::vector<double>> prices = price(matrix);
    std::vector<std::vector<double>> deltas = delta(h, matrix);
    std::vector<double>gammas = gamma(h, matrix);

    // Send data to an output file
    Output_::csv(mesh, prices, deltas, gammas);
}

/**
 * Core pricing functionality for this European Option
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return A matrix of Call and Put prices
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::price() const {
    return price(T, sig, r, S, K, b);
}

/**
 * Receives a matrix of options and prices each of of them
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param matrix Option parameters
 * @return A matrix of option prices
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double> >
EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::price(const std::vector<std::vector<double> > &matrix) {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > prices;

    for (const auto &row : matrix) {
        // Each row in the matrix has a Call and Put price
        prices.push_back(price(row[0], row[1], row[2], row[3], row[4], row[5])[0]);
    }
    return prices;
}

/*
 * Private helper function used to price this option or option data provided by the input matrix
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-free rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of carry
 * @return A vector of Call and Put prices
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<std::vector<double>> EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::price(double T_, double sig_, double r_,
        double S_, double K_, double b_) {

    std::vector<std::vector<double>> prices;

    double tmp = sig_ * sqrt(T_);
    double d1 = (log(S_ / K_) + (b_ + (sig_ * sig_) * 0.5) * T_) / tmp;
    double d2 = d1 - tmp;

    // Call and Put prices
    double call = (S_ * exp((b_ - r_) * T_) * RNG_::CDF(d1)) - (K_ * exp(-r_ * T_) * RNG_::CDF(d2));
    double put = (K_ * exp(-r_ * T_) * RNG_::CDF(-d2)) - (S_ * exp((b_ - r_) * T_) * RNG_::CDF(-d1));

    prices.push_back({call, put});

    return prices;
}

/* ********************************************************************************************************************
 * Put Call Parity
 *********************************************************************************************************************/

/**
 * A mechanism to calculate the call (or put) price for a corresponding put (or call) price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param optionPrice
 * @param optType_ Call or Put. The default value is a Call
 * @return The price that satisfies the put-call parity relationship
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::putCallParity(double optionPrice, const std::string& optType_) const {
    if (optType_ == "Put" || optType_ == "put") {
        return optionPrice + S - (K * exp(-r * T));
    } else {
        return optionPrice + (K * exp(-r * T)) - S;
    }
}

/**
 * Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param putPrice
 * @param callPrice
 * @return True if the relationship is satisfied. Otherwise false
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
bool EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::putCallParity(double callPrice, double putPrice) const {
    return putCallParity(callPrice, putPrice, T, K, r, S);
}

/*
 * Helper function to check if a given set of call (C) and put (P) prices satisfy parity (tolerance = 1e-5)
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param C Call price
 * @param P Put price
 * @param T_ Expiry
 * @param K_ Strike price
 * @param r_ Risk-Free Rate
 * @param S_ Spot price
 * @return True if Put-Call Parity is satisfied. False otherwise
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
bool EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::putCallParity(double C, double P, double T_, double K_, double r_,
        double S_) {
    return ((C + (K_ * exp(-r_ * T_))) - (P + S_)) <= 1e-5;
}

/* ********************************************************************************************************************
 * Accessors
 *********************************************************************************************************************/

/**
 * Accessor that retrieves this options Expiry
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Expiry of this Option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::expiry() const {return T;}

/**
 * Accessor that retrieves this options Volatility
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Volatility of this option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::vol() const { return sig; }

/**
 * Accessor that retrieves this options Risk-Free Rate
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Risk-Free Rate of this option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::riskFree() const { return r; }

/**
 * Accessor that retrieves this options Spot price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Spot price of this option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::spot() const { return S; }

/**
 * Accessor that retrieves this options Strike price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Strike price of this option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::strike() const { return K; }

/**
 * Accessor that retrieves this options Cost of Carry
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Cost of Carry of this option
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::carry() const { return b; }

/* ********************************************************************************************************************
 * Mutators
 *********************************************************************************************************************/

/**
 * Mutator that sets this options parameters to the values specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param T_ Expiry
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::setOptionData(double T_, double sig_, double r_, double S_,
        double K_, double b_) {
    T = T_;
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
}

/**
 * Mutator that sets this options Expiry to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param T_ Expiry
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::expiry(double T_) {T = T_;}

/**
 * Mutator that sets this options Volatility to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param sig_ Volatility
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::vol(double sig_) {sig = sig_;}

/**
 * Mutator that sets this options Risk-Free Rate to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param r_ Risk-free rate
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::riskFree(double r_) {r = r_;}

/**
 * Mutator that sets this options Spot price to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param S_ Spot price
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::spot(double S_) {S = S_;}

/**
 * Mutator that sets this options Strike price to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param K_ Strike price
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::strike(double K_) {K = K_;}

/**
 * Mutator that sets this options Cost of Carry to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param b_ Cost of Carry
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void EuropeanOption<Mesher_, Matrix_, RNG_, Output_>::carry(double b_) {b = b_;}

#endif