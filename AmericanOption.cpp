/**********************************************************************************************************************
 * A financial instrument
 *
 * Created by Michael Lewis on 8/22/20.
 *********************************************************************************************************************/

#ifndef AMERICANOPTION_CPP
#define AMERICANOPTION_CPP

#include "AmericanOption.hpp"

/**
 * Initialize a new perpetual American Option with default parameters provided by the C++ for Financial Engineering
 * course through QuantNet and Baruch College
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @throws OutOfMemoryError Indicates insufficient memory for this new AmericanOption
 */
template<typename Mesher_, typename Matrix_, typename Output_>
AmericanOption<Mesher_, Matrix_, Output_>::AmericanOption() : Mesher_(), Matrix_(), Output_(), sig(0.1), r(0.1),
S(110), K(100), b(0.02) {}

/**
 * Initialize a new perpetual American Option, whose data members will be a deep copy of the source
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source An AmericanOption whose data members will be deeply copied into this AmericanOption
 * @throws OutOfMemoryError Indicates insufficient memory for this new AmericanOption
 */
template<typename Mesher_, typename Matrix_, typename Output_>
AmericanOption<Mesher_, Matrix_, Output_>::AmericanOption(const AmericanOption<Mesher_, Matrix_, Output_> &source)
: Mesher_(), Matrix_(), Output_(), sig(source.sig), r(source.r), S(source.S), K(source.K), b(source.b) {}

/**
 * Initialize a new perpetual American Option with the specified parameters
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param sig_ Volatility
 * @param r_ Risk free rate
 * @param S_ Current price of underlying
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @throws OutOfMemoryError Indicates insufficient memory for this new AmericanOption
 */
template<typename Mesher_, typename Matrix_, typename Output_>
AmericanOption<Mesher_, Matrix_, Output_>::AmericanOption(double sig_, double r_, double S_, double K_, double b_) :
        Mesher_(), Matrix_(), Output_(), sig(sig_), r(r_), S(S_), K(K_), b(b_) {}

/**
 * Destroy's this AmericanOption
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 */
template<typename Mesher_, typename Matrix_, typename Output_>
AmericanOption<Mesher_, Matrix_, Output_>::~AmericanOption<Mesher_, Matrix_, Output_>() {}

/* ********************************************************************************************************************
 * Operator Overloading
 *********************************************************************************************************************/

/**
 * Deeply copy the source data members into this American Option
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param source An American Option whose data members will be deeply copied into this American Option instance
 * @return This American Option whose data members are a deep copy of the sources data members
 */
template<typename Mesher_, typename Matrix_, typename Output_>
AmericanOption<Mesher_, Matrix_, Output_>&
AmericanOption<Mesher_, Matrix_, Output_>::operator=(const AmericanOption<Mesher_, Matrix_, Output_> &source) {
    // Avoid self-assign
    if (this == &source) { return *this; }

    sig = source.sig;
    r = source.r;
    S = source.S;
    K = source.K;
    b = source.b;

    return *this;
}

/* ********************************************************************************************************************
 * Core pricing functions - American Options
 *********************************************************************************************************************/

/**
 * The core pricing engine
 * @note This version sends option data to an Output class, which sends data to a CSV file on the current path
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param start Start point of interval
 * @param stop End point of interval
 * @param step The step size within the interval
 * @param property The option parameter which will be monotonically increased by the Mesher
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::price(double start, double stop, double step,
        const std::string& property) const {

    std::vector<double> mesh = Mesher_::xarr(start, stop, step);     // Generate the mesh points for the matrix

    std::vector<std::vector<double>> matrix = Matrix_::matrix(mesh, property, sig, r, S, K, b);

    // Create and fill containers with option data
    std::vector<std::vector<double>> prices = price(matrix);

    // Send data to an output file
    Output::csv(mesh, prices);
}

/**
 * Core pricing functionality for this American Option
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return A matrix of Call and Put prices
 */
template<typename Mesher_, typename Matrix_, typename Output_>
std::vector<std::vector<double>> AmericanOption<Mesher_, Matrix_, Output_>::price() const {
    return price(sig, r, S, K, b);
}

/**
 * Receives a matrix of options and prices each of of them
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param matrix Option parameters
 * @return A matrix of option prices. Each row in the matrix has a Call price and a Put price
 */
template<typename Mesher_, typename Matrix_, typename Output_>
std::vector<std::vector<double> >
AmericanOption<Mesher_, Matrix_, Output_>::price(const std::vector<std::vector<double> > &matrix) {

    // Create a new container for each new matrix
    std::vector<std::vector<double> > prices;

    for (const auto &row : matrix) {
        // Each row in the matrix has a Call and Put price
        prices.push_back(price(row[0], row[1], row[2], row[3], row[4])[0]);
    }
    return prices;
}

/*
 * Private helper function used to price this option or option data provided by the input matrix
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @return A matrix of Call and Put prices
 */
template<typename Mesher_, typename Matrix_, typename Output_>
std::vector<std::vector<double>>
AmericanOption<Mesher_, Matrix_, Output_>::price(double sig_, double r_, double S_, double K_, double b_) {

    std::vector<std::vector<double>> prices;

    double sig2 = sig_ * sig_;
    double fac = b_ / sig2 - 0.5;
    fac *= fac;
    double y1 = 0.5 - b_ / sig2 + sqrt(fac + 2.0 * r_ / sig2);
    double y2 = 0.5 - b_ / sig2 - sqrt(fac + 2.0 * r_ / sig2);

    // Temp variables create a row for each Call and Put
    double call, put;

    // Call price
    if (1.0 == y1) {
        call = S_;
    } else {
        double fac2 = ((y1 - 1.0) * S_) / (y1 * K_);
        double c = K_ * pow(fac2, y1) / (y1 - 1.0);
        call = c;
    }

    // Put price
    if (0.0 == y2) {
        put = S_;
    } else {
        double fac2 = ((y2 - 1.0) * S_) / (y2 * K_);
        double p = K_ * pow(fac2, y2) / (1.0 - y2);
        put = p;
    }

    prices.push_back({call, put});
    return prices;
}

/* ********************************************************************************************************************
 * Accessors
 *********************************************************************************************************************/

/**
 * Accessor that retrieves this options Volatility
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Volatility of this option
 */
template<typename Mesher_, typename Matrix_, typename Output_>
double AmericanOption<Mesher_, Matrix_, Output_>::vol() const { return sig; }

/**
 * Accessor that retrieves this options Risk-Free Rate
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Risk-Free Rate of this option
 */
template<typename Mesher_, typename Matrix_, typename Output_>
double AmericanOption<Mesher_, Matrix_, Output_>::riskFree() const { return r; }

/**
 * Accessor that retrieves this options Spot price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Spot price of this option
 */
template<typename Mesher_, typename Matrix_, typename Output_>
double AmericanOption<Mesher_, Matrix_, Output_>::spot() const { return S; }

/**
 * Accessor that retrieves this options Strike price
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Strike price of this option
 */
template<typename Mesher_, typename Matrix_, typename Output_>
double AmericanOption<Mesher_, Matrix_, Output_>::strike() const { return K; }

/**
 * Accessor that retrieves this options Cost of Carry
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @return Cost of Carry of this option
 */
template<typename Mesher_, typename Matrix_, typename Output_>
double AmericanOption<Mesher_, Matrix_, Output_>::carry() const { return b; }

/* ********************************************************************************************************************
 * Mutators
 *********************************************************************************************************************/

/**
 * Mutator that sets this options parameters to the values specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param sig_ Volatility
 * @param r_ Risk-free rate
 * @param S_ Spot price
 * @param K_ Strike price
 * @param b_ Cost of carry
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::setOptionData(double sig_, double r_, double S_, double K_, double b_) {
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
}

/**
 * Mutator that sets this options Volatility to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param sig_ Volatility
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::vol(double sig_) {sig = sig_;}

/**
 * Mutator that sets this options Risk-Free Rate to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param r_ Risk-free rate
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::riskFree(double r_) {r = r_;}

/**
 * Mutator that sets this options Spot price to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param S_ Spot price
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::spot(double S_) {S = S_;}

/**
 * Mutator that sets this options Strike price to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param K_ Strike price
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::strike(double K_) {K = K_;}

/**
 * Mutator that sets this options Cost of Carry to the value specified in the argument list
 * @tparam Mesher_ Monotonically increases the specified option property. The interval is [start, stop] and each point
 * is separated by the step
 * @tparam Matrix_ Creates a matrix of option parameters where each new row has a property that has been monotonically
 * increased by the Mesher
 * @tparam Output_ Output class that sends option data to a file specified by the user
 * @param b_ Cost of Carry
 */
template<typename Mesher_, typename Matrix_, typename Output_>
void AmericanOption<Mesher_, Matrix_, Output_>::carry(double b_) {b = b_;}

#endif