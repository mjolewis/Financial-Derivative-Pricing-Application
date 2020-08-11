/**********************************************************************************************************************
 * Assemble option data for the pricing engine
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <vector>

#include "Option.hpp"

class Input {
private:
    // Required option data
    double T;                                    // Expiry time/maturity. E.g. T = 1 means one year
    double sig;                                  // Volatility
    double r;                                    // Risk-free interest rate
    double S;                                    // Spot price
    double K;                                    // Strike price
    double b;                                    // Cost of carry; b = r for Black-Scholes equity option model

    // Model parameters
    std::string optType;                         // Call or Put
    std::string optFlavor;                       // European or American
    std::string uName;                           // Name of underlying asset
    std::vector<double> meshData;                // The domain of integration and factor

    Option option;                               // Option data container
public:
    // Constructors and destructor
    Input();
    Input(const Input &source);
    virtual ~Input();

    // Operator overloading
    Input &operator=(const Input &source);

    // Getters
    const Option& getOptionData() const;         // Simple getter that returns the option object

    const std::vector<double>& setMeshData();    // Provide a console interface to dynamically get mesh data
    const Option& setOptionData();               // Provide a console interface to dynamically get option data
};

#endif //INPUT_HPP
