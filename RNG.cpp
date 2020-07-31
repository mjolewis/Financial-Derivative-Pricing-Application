/**********************************************************************************************************************
 * Function definitions for RNG.hpp
 *
 * Generates different types of distributions that will be used by the Pricer. The distributions requirea random
 * number generator and the default will be Mersenne Twister.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include <boost/random.hpp>

#include "RNG.hpp"

namespace MJL {
    namespace Pricers {

        /**
         * Initialize a new RNG
         * @throws OutOfMemoryError Indicates insufficient memory for this RNG
         */
        RNG::RNG() {}

        /**
         * Initialize a new RNG with the specified parameters
         * @param RNGName_ The random number generator to use
         * @throws OutOfMemoryError Indicates insufficient memory for this RNG
         */
        RNG::RNG(const std::string& RNGName_) : RNGName(RNGName_){}

        /**
         * Initialize a new RNG with the specified parameters
         * @param source A RNG whose data members will be used to initialize this RNG
         * @throws OutOfMemoryError Indicates insufficient memory for this RNG
         */
        RNG::RNG(const RNG &source) : RNGName(source.RNGName) {}

        /**
         * Destroy this RNG
         */
        RNG::~RNG() {}

        /**
         * Create a deep copy of the source
         * @param source A RNG to deeply copy
         * @return A reference to this RNG
         */
        RNG & RNG::operator=(const RNG &source) {
            // Avoid self-assign
            if (this == &source) { return *this; }

            RNGName = source.RNGName;

            return *this;
        }

        /**
         * Generate N(x) for Black-Scholes Pricer
         * @return A Gaussian random variate
         */
        double RNG::MersenneTwister() const {
            boost::random::mt19937 rng;

            // Set the seed using the current time to generate more randomness
            rng.seed(static_cast<uint32_t>(std::time(0)));

            // A normal distribution with a mean of 0 and standard deviation of 1 is known as the Standard Normal Distribution
            boost::normal_distribution<double> N(0, 1);
            return N(rng);
        }

        const std::string& RNG::getRNGName() const {return RNGName;}
    }
}
