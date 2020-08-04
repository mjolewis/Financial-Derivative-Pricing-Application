/**********************************************************************************************************************
 * Function declarations for Pricer.hpp
 *
 * A financial derivatives pricing engine that employs the Black-Scholes formula with exact methods.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_HPP
#define PRICER_HPP

#include <vector>
#include <boost/tuple/tuple_io.hpp>

#include "Input.hpp"

typedef  boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

template<typename Input_, typename RNG_, typename Instrument_>
class Pricer : public Input_, public RNG_, public Instrument_ {

private:
    OptionData optionData;                            // Holds the option data; Provided via Input.cpp
    double optionPrice;                               // Output of the current option price

    // Used for output only
    std::vector<double> optionPrices;                 // Output of option prices

public:
    // Constructors and destructors
    Pricer();
    Pricer(const OptionData& optionData_);
    Pricer(const Pricer& source);
    virtual ~Pricer();

    // Operator overloading
    Pricer& operator=(const Pricer& source);

    // Getters
    const OptionData& getOptionData() const;
    std::vector<double> getOptionPrices() const;
    void getOptionInput();                            // Uses Input.cpp to set up a console UI to input option data

    // Setters
    void setOptionData(const OptionData& optionData_);

    // Core Pricing engine that implements the Black-Scholes pricing formula
    double price();
    double callPrice(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optFlavor_);
    double putPrice(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optFlavor_);

    bool putCallParity(double putPrice, double callPrice) const;
};

#ifndef PRICER_CPP
#include "Pricer.cpp"

#endif // PRICER_CPP
#endif // PRICER_HPP
