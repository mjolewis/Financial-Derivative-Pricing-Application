/**********************************************************************************************************************
 * Generates different types of distributions for the Pricer.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef RNG_HPP
#define RNG_HPP

#include <string>
#include <ctime>

#include "boost/random.hpp"
#include "boost/math/distributions/normal.hpp"

class RNG {
private:
    std::string RNGName;                 // Name of random number generator
public:

    // Constructors and Destructors
    RNG();
    RNG(const RNG &source);
    explicit RNG(const std::string &RNGName_);
    virtual ~RNG();

    // Operator overloading
    RNG &operator=(const RNG &source);

    // Getters
    const std::string &getRNGName() const;

    // Core functionality
    double MersenneTwister();            // Generate a standard normal distribution using Mersenne Twister
    double CDF(double x);                // Cumulative normal distribution function
    double PDF(double x);                // Normal (Gaussian) probability density function
};

#endif //RNG_HPP
