/**********************************************************************************************************************
 * Black-Scholes pricing application. Provides access to the core Option pricing and sensitivity engine
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_CPP
#define PRICER_CPP

#include "Pricer.hpp"
#include "Mesher.hpp"
#include "Matrix.hpp"
#include "Output.hpp"
#include "RNG.hpp"

/**
 * Initialize a new Pricer
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
Pricer<Mesher_, Matrix_, RNG_, Output_>::Pricer() : Mesher_(), Matrix_(), RNG_(), Output_() {}

/**
 * Initialize a new Pricer
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param optionData_ A {@link boost::tuple} with T, sig, r, S, K, optType
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
Pricer<Mesher_, Matrix_, RNG_, Output_>::Pricer(const Option &option_) : Mesher_(), Matrix_(), RNG_(), Output_() {}

/**
 * Initialize a new Pricer whose members are a deep copy of the source
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source A Pricer whose data members will be deeply copied into this new Pricer
 * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
Pricer<Mesher_, Matrix_, RNG_, Output_>::Pricer(const Pricer &source) : Mesher_(), Matrix_(), RNG_(), Output_() {}

/**
 * Destroy this Pricer
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
Pricer<Mesher_, Matrix_, RNG_, Output_>::~Pricer() {}

/**
 * Deeply copy the source data members into this Pricer
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam RNG_ Provides access to the Boost Random library to generate Gaussian variates
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source A Pricer whose data members will be deeply copied into this new Pricer
 * @return A Pricer whose data members are a deep copy of the source data members
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
Pricer<Mesher_, Matrix_, RNG_, Output_> &Pricer<Mesher_, Matrix_, RNG_, Output_>
        ::operator=(const Pricer<Mesher_, Matrix_, RNG_, Output_> &source) {

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
 * Option sensitivities (Greeks)
 *********************************************************************************************************************/

/**
 * Calculate closed form solution for Delta
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
 * @return A vector of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double> Pricer<Mesher_, Matrix_, RNG_, Output_>::delta(double T, double sig, double r, double S,
                                             double K, double b) const {

    std::vector<double> deltas;

    double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));

    // Add call delta then put delta
    deltas.push_back({exp((b - r) * T) * RNG_::CDF(d1)});                 // Call delta
    deltas.push_back({exp((b - r) * T) * (RNG_::CDF(d1) - 1.0)});         // Put delta

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
Pricer<Mesher_, Matrix_, RNG_, Output_>::delta(const std::vector<std::vector<double> > &matrix) const {

    std::vector<std::vector<double> > deltas;

    for (const auto &i : matrix) {
        deltas.push_back(delta(i[0], i[1], i[2], i[3], i[4], i[5]));      // Each row contains Call and Put Deltas
    }
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
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-free rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of carry
 * @return The delta call or delta put approximation, which depends on the type of option provided
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double> Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaAmerican(double h, double T, double sig, double r, double S,
                                                                   double K, double b) const {

    // Call and Put Deltas
    std::vector<double> deltas;

    // Placeholders for final numerator values
    std::vector<double> LHS = priceAmerican(T, sig, r, S + h, K, b);
    std::vector<double> RHS = priceAmerican(T, sig, r, S - h, K, b);

    // Divided differences method
    deltas.push_back((LHS[0] - RHS[0]) / (2 * h));              // Call prices
    deltas.push_back((LHS[1] - RHS[1]) / (2 * h));              // Put prices

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
 * @param option An option with T, sig, r, S, K, b
 * @return A vector of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double> Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaAmerican(double h, const std::vector<double> &option) const {

    // Call and Put Deltas
    std::vector<double> deltas;

    // Input for divided differences numerator
    double S1 = option[3] + h;
    double S2 = option[3] - h;

    // Placeholders for final numerator values
    std::vector<double> LHS = priceAmerican(option[0], option[1], option[2], S1, option[4], option[5])[0];
    std::vector<double> RHS = priceAmerican(option[0], option[1], option[2], S2, option[4], option[5])[0];

    // Divided differences method
    deltas.push_back((LHS[0] - RHS[0]) / (2 * h));              // Call prices
    deltas.push_back((LHS[1] - RHS[1]) / (2 * h));              // Put prices

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
Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaAmerican(double h, const std::vector<std::vector<double> > &matrix) const {

    // Container for divided differences results
    std::vector<std::vector<double>> deltaPrices;

    for (const auto &row : matrix) {
        deltaPrices.push_back(deltaAmerican(h, row));
    }

    return deltaPrices;
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
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-free rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of carry
 * @return The delta call or delta put approximation, which depends on the type of option provided
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double> Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaEuropean(double h, double T, double sig, double r, double S,
                                                                   double K, double b) const {

    // Call and Put Deltas
    std::vector<double> deltas;

    // Placeholders for final numerator values
    std::vector<double> LHS = priceEuropean(T, sig, r, S + h, K, b);
    std::vector<double> RHS = priceEuropean(T, sig, r, S - h, K, b);

    // Divided differences method
    deltas.push_back((LHS[0] - RHS[0]) / (2 * h));              // Call prices
    deltas.push_back((LHS[1] - RHS[1]) / (2 * h));              // Put prices

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
 * @return A vector of Call and Put Deltas
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
std::vector<double> Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaEuropean(double h, const std::vector<double> &option) const {

    // Call and Put Deltas
    std::vector<double> deltas;

    // Input for divided differences numerator
    double S1 = option[3] + h;
    double S2 = option[3] - h;

    // Placeholders for final numerator values
    std::vector<double> LHS = priceEuropean(option[0], option[1], option[2], S1, option[4], option[5])[0];
    std::vector<double> RHS = priceEuropean(option[0], option[1], option[2], S2, option[4], option[5])[0];

    // Divided differences method
    deltas.push_back((LHS[0] - RHS[0]) / (2 * h));              // Call prices
    deltas.push_back((LHS[1] - RHS[1]) / (2 * h));              // Put prices

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
Pricer<Mesher_, Matrix_, RNG_, Output_>::deltaEuropean(double h, const std::vector<std::vector<double> > &matrix) const {

    // Container for divided differences results
    std::vector<std::vector<double>> deltaPrices;

    for (const auto &row : matrix) {
        deltaPrices.push_back(deltaEuropean(h, row));
    }

    return deltaPrices;
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
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-free rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of carry
 * @return The rate of change with respect to the input parameters
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double Pricer<Mesher_, Matrix_, RNG_, Output_>::gamma(double T, double sig, double r, double S, double K, double b) const {
    double tmp = sig * sqrt(T);

    double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;

    double n1 = RNG_::PDF(d1);

    return (n1 * exp((b - r) * T)) / (S * tmp);
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
std::vector<std::vector<double>>
Pricer<Mesher_, Matrix_, RNG_, Output_>::gamma(const std::vector<std::vector<double> > &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammas;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto &i : matrix) {
        gammas.push_back({gamma(i[0], i[1], i[2], i[3], i[4], i[5])});
    }
    return gammas;
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
double Pricer<Mesher_, Matrix_, RNG_, Output_>::gammaAmerican(double h, const std::vector<double> &option) const {

    // Input for divided differences numerator
    double S1 = (priceAmerican(option[0], option[1], option[2], option[3] + h, option[4], option[5])[0][0]);
    double S2 = 2 * (priceAmerican(option[0], option[1], option[2], option[3], option[4], option[5])[0][0]);
    double S3 = (priceAmerican(option[0], option[1], option[2], option[3] - h, option[4], option[5])[0][0]);

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
std::vector<std::vector<double>>
Pricer<Mesher_, Matrix_, RNG_, Output_>::gammaAmerican(double h, const std::vector<std::vector<double>> &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammas;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto &i : matrix) {
        gammas.push_back({gammaAmerican(h, i)});
    }

    return gammas;
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
double Pricer<Mesher_, Matrix_, RNG_, Output_>::gammaEuropean(double h, const std::vector<double> &option) const {

    // Input for divided differences numerator
    double S1 = (priceEuropean(option[0], option[1], option[2], option[3] + h, option[4], option[5])[0][0]);
    double S2 = 2 * (priceEuropean(option[0], option[1], option[2], option[3], option[4], option[5])[0][0]);
    double S3 = (priceEuropean(option[0], option[1], option[2], option[3] - h, option[4], option[5])[0][0]);

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
std::vector<std::vector<double>>
Pricer<Mesher_, Matrix_, RNG_, Output_>::gammaEuropean(double h, const std::vector<std::vector<double>> &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > gammas;

    // Calculate exact gamma and put the result into the output matrix
    for (const auto &i : matrix) {
        gammas.push_back({gammaEuropean(h, i)});
    }

    return gammas;
}

/**
 * Calculate closed form solution for Vega
 * @note Measures option sensitivity to implied vol (e.g. change in the option price per point change in implied vol)
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
 * @return The rate of change in the option price with respect to volatility
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
double Pricer<Mesher_, Matrix_, RNG_, Output_>::vega(double T, double sig, double r, double S, double K, double b) const {

    double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / (sig * sqrt(T));

    return (S * exp((b - r) * T) * RNG_::PDF(d1) * sqrt(T));
}

/* ********************************************************************************************************************
 * Core pricing functions
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
 * @param option A financial deriviative with parameters T, sig, r, S, K, b, optType, optFlavor
 * @param property The option parameter which will be monotonically increased by the Mesher
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void
Pricer<Mesher_, Matrix_, RNG_, Output_>::priceAmerican(double h, double start, double stop, double step, const Option& option,
const std::string& property) const {

    std::vector<double> mesh = Mesher_::xarr(start, stop, step);     // Generate the mesh points for the matrix

    std::vector<std::vector<double>> matrix = Matrix_::americanMatrix(mesh, option, property);

    // Create and fill containers with option data
    std::vector<std::vector<double>> prices = priceAmerican(matrix);
    std::vector<std::vector<double>> deltas = deltaAmerican(h, matrix);

    // Send data to an output file
    Output::sendToFile(mesh, prices, deltas);
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
Pricer<Mesher_, Matrix_, RNG_, Output_>::priceAmerican(const std::vector<std::vector<double> > &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > prices;

    for (const auto &row : matrix) {
        // Each row in the matrix has a Call and Put price
        prices.push_back(priceAmerican(row[0], row[1], row[2], row[3], row[4], row[5])[0]);
    }
    return prices;
}

/**
 * The core pricing engine that uses the Black-Scholes formula
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
std::vector<std::vector<double>> Pricer<Mesher_, Matrix_, RNG_, Output_>::priceAmerican(double T, double sig, double r, double S,
        double K, double b) const {

    std::vector<std::vector<double>> prices;

    double sig2 = sig * sig;
    double fac = b / sig2 - 0.5;
    fac *= fac;
    double y1 = 0.5 - b / sig2 + sqrt(fac + 2.0 * r / sig2);
    double y2 = 0.5 - b / sig2 - sqrt(fac + 2.0 * r / sig2);

    // Temp variables create a row for each Call and Put
    double call, put;

    // Call price
    if (1.0 == y1) {
        call = S;
    } else {
        double fac2 = ((y1 - 1.0) * S) / (y1 * K);
        double c = K * pow(fac2, y1) / (y1 - 1.0);
        call = c;
    }

    // Put price
    if (0.0 == y2) {
        put = S;
    } else {
        double fac2 = ((y2 - 1.0) * S) / (y2 * K);
        double p = K * pow(fac2, y2) / (1.0 - y2);
        put = p;
    }

    prices.push_back({call, put});
    return prices;
}

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
 * @param option A financial deriviative with parameters T, sig, r, S, K, b, optType, optFlavor
 * @param property The option parameter which will be monotonically increased by the Mesher
 */
template<typename Mesher_, typename Matrix_, typename RNG_, typename Output_>
void
Pricer<Mesher_, Matrix_, RNG_, Output_>::priceEuropean(double h, double start, double stop, double step, const Option& option,
                                               const std::string& property) const {

    std::vector<double> mesh = Mesher_::xarr(start, stop, step);     // Generate the mesh points for the matrix

    std::vector<std::vector<double>> matrix = Matrix_::europeanMatrix(mesh, option, property);

    // Create and fill containers with option data
    std::vector<std::vector<double>> prices = priceEuropean(matrix);
    std::vector<std::vector<double>> deltas = deltaEuropean(h, matrix);
    std::vector<std::vector<double>> gammas = gammaEuropean(h, matrix);

    // Send data to an output file
    Output::sendToFile(mesh, prices, deltas, gammas);
}

/**
 * The core pricing engine that uses the Black-Scholes formula
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
std::vector<std::vector<double>> Pricer<Mesher_, Matrix_, RNG_, Output_>::priceEuropean(double T, double sig, double r,
        double S, double K, double b) const {

    std::vector<std::vector<double>> prices;

    double tmp = sig * sqrt(T);
    double d1 = (log(S / K) + (b + (sig * sig) * 0.5) * T) / tmp;
    double d2 = d1 - tmp;

    // Call price
    double call = (S * exp((b - r) * T) * RNG_::CDF(d1)) - (K * exp(-r * T) * RNG_::CDF(d2));

    // Put price
    double put = (K * exp(-r * T) * RNG_::CDF(-d2)) - (S * exp((b - r) * T) * RNG_::CDF(-d1));

    prices.push_back({call, put});

    return prices;
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
Pricer<Mesher_, Matrix_, RNG_, Output_>::priceEuropean(const std::vector<std::vector<double> > &matrix) const {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > prices;

    for (const auto &row : matrix) {
        // Each row in the matrix has a Call and Put price
        prices.push_back(priceEuropean(row[0], row[1], row[2], row[3], row[4], row[5])[0]);
    }
    return prices;
}

#endif