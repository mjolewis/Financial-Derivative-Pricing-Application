/**********************************************************************************************************************
 * Function declarations for Pricer.hpp
 *
 * A financial derivatives pricing and sensitivity engine that employs the Black-Scholes formula
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_HPP
#define PRICER_HPP

#include <vector>
#include <boost/tuple/tuple_io.hpp>

#include "Input.hpp"
#include "Instrument.hpp"

typedef  boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

template<typename Input_, typename RNG_, typename Mesher_>
class Pricer : public Input_, public RNG_, public Mesher_ {

private:
    std::vector<double> meshPoints;                   // Holds the mesh points provided by Mesher.cpp
    OptionData optionData;                            // Holds the option data; Provided via Input.cpp
    double optionPrice;                               // Current option price
    double deltaPrice;                                // Call delta or Put delta price

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
    void getMeshPoints(const std::string& property);  // Uses Mesher.cpp to generate a set of mesh points

    // Setters
    void setOptionData(const OptionData& optionData_);

    // Core Pricing engines
    double price();
    const std::vector<std::vector<double> > price(const std::vector<std::vector<double> >& matrix,
            const std::string& optType_ = "Call", const std::string& optFlavor_ = "European");
    double price(double T_, double sig_, double r_, double S_, double K_, double b_,
            const std::string& optType = "Call", const std::string& optFlavor_ = "European");

    // Option sensitivities (Greeks)
    double delta(double T_, double sig_, double r_, double S_, double K_, double b_, const std::string& optType = "Call");
    const std::vector<std::vector<double>> delta(const std::vector<std::vector<double>>& matrix, const std::string& optType_ = "Call");

    double gamma(double T_, double sig_, double r_, double S_, double K_, double b_);
    const std::vector<std::vector<double>> gamma(const std::vector<std::vector<double>> &matrix);
};

#ifndef PRICER_CPP
#include "Pricer.cpp"

#endif // PRICER_CPP
#endif // PRICER_HPP
