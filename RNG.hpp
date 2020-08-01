/**********************************************************************************************************************
 * Function definitions for RNG.hpp
 *
 * Generates different types of distributions that will be used by the Pricer. The distributions requirea random
 * number generator and the default will be Mersenne Twister.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef RNG_HPP
#define RNG_HPP

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
};

#endif //RNG_HPP
