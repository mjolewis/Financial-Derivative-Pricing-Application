/**********************************************************************************************************************
 * Generates model parameter for EuropeanOption
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "RNG.hpp"

/**
 * Initialize a new RNG
 * @throws OutOfMemoryError Indicates insufficient memory for this RNG
 */
RNG::RNG() {}

/**
 * Initialize a new RNG with the specified parameters
 * @param source A RNG whose data members will be used to initialize this RNG
 * @throws OutOfMemoryError Indicates insufficient memory for this RNG
 */
RNG::RNG(const RNG &source) {}

/**
 * Destroy this RNG
 */
RNG::~RNG() {}

/**
 * Create a deep copy of the source
 * @param source A RNG to deeply copy
 * @return A reference to this RNG
 */
RNG &RNG::operator=(const RNG &source) {
    // Avoid self-assign
    if (this == &source) { return *this; }

    return *this;
}

/**
 * Generate N(x) for Black-Scholes EuropeanOption
 * @return Probability that X will take on a value less than or equal to x
 */
double RNG::CDF(double x) const {
    boost::math::normal norm;
    return boost::math::cdf(norm, x);
}

/**
 * Generate n(x) for Black-Scholes EuropeanOption
 * @return Probability that X will take on a value greater than x
 */
double RNG::PDF(double x) const {
    boost::math::normal norm;
    return boost::math::pdf(norm, x);
}

/**
 * Generate N(x) for Black-Scholes EuropeanOption
 * @return A Gaussian random variate
 */
double RNG::MersenneTwister() {
    boost::random::mt19937 rng;

    // Set the seed using the current time to generate more randomness
    rng.seed(static_cast<unsigned int> (std::time(0)));

    // A normal distribution with a mean of 0 and standard deviation of 1 is known as the Standard Normal Distribution
    boost::normal_distribution<double> N(0, 1);
    return N(rng);
}
