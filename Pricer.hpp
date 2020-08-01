/**********************************************************************************************************************
 * Function declarations for Pricer.hpp
 *
 * A financial derivatives pricing engine that employs the Black-Scholes formula with exact methods.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef PRICER_HPP
#define PRICER_HPP

#include <boost/tuple/tuple_io.hpp>
#include <vector>
#include "Input.hpp"

typedef  boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;

namespace MJL {
    namespace Pricers {

        template<typename Input_, typename RNG_, typename Instrument_>
        class Pricer : public MJL::Input::Input {

        private:
            OptionData optionData;                         // Holds the option data; Provided via Input.cpp
            std::vector<double> optionPrices;              // Output of option prices
            double optionPrice;                            // Output of the current option price

        public:
            // Constructors and destructors
            Pricer(); // Default constructor
            Pricer(const OptionData& optionData_, const std::vector<double>& optionPrices_);
            Pricer(const Pricer& source);
            virtual ~Pricer();

            // Operator overloading
            Pricer& operator=(const Pricer& source);

            // Getters
            const OptionData& getOptionData() const;
            std::vector<double> getOptionPrices() const;

            // Setters
            void setOptionData(const OptionData& optionData_);

            // Core Pricing engine that implements the Black-Scholes pricing formula.
            double price();
        };
    }
}

#ifndef PRICER_CPP
#include "Pricer.cpp"

#endif // PRICER_CPP
#endif // PRICER_HPP
