/**********************************************************************************************************************
 * Assemble option data for the pricing engine
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include <string>
#include <vector>

#include <boost/tuple/tuple.hpp>


// Stores option data (e.g. expiry, volatility, risk-free rate, spot, option type, optFlavor
typedef boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

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
    std::vector<double> meshData;                // The domain of integration and factor
public:
    // Constructors and destructor
    Input();
    explicit Input(const OptionData &optionData_);
    Input(double T_, double sig_, double r_, double S_, double K_, double b_, std::string &optType_, std::string &optFlavor_);
    Input(const Input &source);
    virtual ~Input();

    // Operator overloading
    Input &operator=(const Input &source);

    // Getters
    const std::vector<double>& getMeshData();    // Provide a console interface to dynamically get mesh data
    OptionData getOptionData() const;            // Simple getter that returns the option object
    OptionData getOptionInput();                 // Provide a console interface to dynamically get option data

    // Setters
    void setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_, const std::string &optType_, const std::string &optFlavor_);
};

#endif //INPUT_HPP
