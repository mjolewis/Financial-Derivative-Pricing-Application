/**********************************************************************************************************************
 * Assemble option data for the pricing engine
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/tuple/tuple_io.hpp>
#include <vector>
#include <string>

// Stores option data (e.g. expiry, volatility, risk-free rate, spot, option type, uName
typedef boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

class Input {
private:
    // Required option data
    double T;                                 // Expiry time/maturity. E.g. T = 1 means one year
    double sig;                               // Volatility
    double r;                                 // Risk-free interest rate
    double S;                                 // Spot price
    double K;                                 // Strike price
    double b;                                 // Cost of carry; b = r for Black-Scholes equity option model
    std::string optType;                      // Call or Put
    std::string uName;                        // European or American
public:
    // Constructors and destructor
    Input();

    explicit Input(const OptionData &optionData_);

    Input(double T_, double sig_, double r_, double S_, double K_, double b_, std::string &optType_,
          std::string &uName_);

    Input(const Input &source);

    virtual ~Input();

    // Operator overloading
    Input &operator=(const Input &source);

    // Getters
    OptionData getOptionData() const;

    // Setters
    OptionData setOptionData();
};

#endif //INPUT_HPP
