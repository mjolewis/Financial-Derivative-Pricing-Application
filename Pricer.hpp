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
#include "Option.hpp"

typedef  boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

template<typename Input_, typename RNG_, typename Mesher_>
class Pricer : public Input_, public RNG_, public Mesher_ {

private:
    OptionData optionData;                            // Holds the option data; Provided via Input.cpp

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

    // Setters
    void setOptionData(const OptionData& optionData_);

    // Core Pricing engines
    double price();
    std::vector<std::vector<double>>
    price(const std::vector<std::vector<double> >& matrix,
            const std::string& optType = "Call", const std::string& optFlavor = "European") const;
    double price(double T, double sig, double r, double S, double K, double b,
            const std::string& optType = "Call", const std::string& optFlavor = "European") const;

    // Exact solutions for option sensitivities (Greeks)
    double delta(double T, double sig, double r, double S, double K, double b, const std::string& optType = "Call") const;
    std::vector<std::vector<double>> delta(const std::vector<std::vector<double>>& matrix, const std::string& optType = "Call") const;
    double gamma(double T, double sig, double r, double S, double K, double b) const;
    std::vector<std::vector<double>> gamma(const std::vector<std::vector<double>>& matrix) const;
    double vega(double T, double sig, double r, double S, double K, double b) const;

    // Divided differences method for option sensitivities (Greeks)
    double delta(double h, const std::vector<double>& option, const std::string &optType = "Call",
            const std::string& optFlavor = "European") const;
    std::vector<std::vector<double>> delta(double h, const std::vector<std::vector<double>>& matrix,
            const std::string &optType = "Call", const std::string& optFlavor = "European") const;
    double gamma(double h, const std::vector<double>& option) const;
    std::vector<std::vector<double>> gamma(double h, const std::vector<std::vector<double>>& matrix) const;
};

#ifndef PRICER_CPP
#include "Pricer.cpp"

#endif // PRICER_CPP
#endif // PRICER_HPP
