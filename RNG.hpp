/**********************************************************************************************************************
 * Generates model parameter for EuropeanOption
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

public:

    // Constructors and Destructors
    RNG();
    RNG(const RNG &source);
    virtual ~RNG();

    // Operator overloading
    RNG &operator=(const RNG &source);

    // Core functionality
    double MersenneTwister();                    // Generate a standard normal distribution using Mersenne Twister
    double CDF(double x) const;                  // Cumulative normal distribution function
    double PDF(double x) const;                  // Normal (Gaussian) probability density function
};

#endif //RNG_HPP
