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
    static double MersenneTwister();             // Generate a standard normal distribution using Mersenne Twister
    static double CDF(double x);                 // Cumulative normal distribution function
    static double PDF(double x);                 // Normal (Gaussian) probability density function
};

#endif //RNG_HPP
