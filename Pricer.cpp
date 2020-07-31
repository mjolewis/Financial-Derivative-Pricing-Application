/**********************************************************************************************************************
 * Function definitions for Pricer.cpp
 *
 * A financial derivatives pricing engine that employs the Black-Scholes formula with exact methods.
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "Pricer.hpp"

#include <boost/tuple/tuple_io.hpp>
#include <iostream>
#include "Input.hpp"

namespace MJL {
    namespace Pricers {

        /**
         * Initialize a new Pricer object
         * @throws OutOfMemoryException Indicates insufficient memory for this new Pricer object
         */
        Pricer::Pricer() {}

        /**
         * Initialize a new Pricer object with the specified parameters
         * @param optionData_ A {@link boost::tuple} containing values to initialize core option data (e.g expiry,
         * volatility, risk-free rate, spot price, strike price, option type)
         * @param optionPrices_ A {@link std::vector<>} containing option prices
         * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
         */
        Pricer::Pricer(const OptionData &optionData_, const std::vector<double>& optionPrices_) :
                                                        optionData(optionData_), optionPrices(optionPrices_) {}
        /**
         * Initialize a deep copy of the specified source
         * @param source A Pricer that will be deeply copied
         * @throws OutOfMemoryError Indicates insufficient memory for this new Pricer
         */
        Pricer::Pricer(const Pricer &source) : optionData(source.optionData), optionPrices(source.optionPrices) {}

        /**
         * Destroy's this Pricer
         */
        Pricer::~Pricer() {}

        /**
         * Create a deep copy of the source Pricer
         * @param source A Pricer that will be deeply copied
         * @return A reference to this Pricer
         */
        Pricer & Pricer::operator=(const Pricer &source) {
            // Avoid self assign
            if (this == &source) { return *this; }

            optionData = source.optionData;
            optionPrices = source.optionPrices;

            return *this;
        }

        /**
         * Accessor function that returns the option data
         * @return A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K, optType)
         */
        const OptionData & Pricer::getOptionData() const {
            return optionData;
        }

        /**
         * Accessor function that returns the option prices
         * @return A {@link std::vector} of option prices
         */
        std::vector<double> Pricer::getOptionPrices() const {
            return optionPrices;
        }

        /**
         * Mutator function that assigns the parameter to this objects optionData member
         * @param optionData_ A {@link boost::tuple<>} containing the core option data (e.g. Expiry, sig, r, S, K,
         * optType)
         */
        void Pricer::setOptionData(const OptionData &optionData_) {
            optionData = optionData_;
        }

        /**
         * The core pricing engine that uses the Black-Scholes formula to price various types of options
         * @return The price of the option
         */
        double Pricer::price() {

            // Transfer option data from the Input
            optionData = MJL::Input::Input::setOptionData();

            // Required option data
            double T = optionData.get<0>();                          // Expiry time/maturity. E.g. T = 1 means one year
            double sig = optionData.get<1>();                        // Volatility
            double r = optionData.get<2>();                          // Risk-free interest rate
            double S = optionData.get<3>();                          // Spot price
            double K = optionData.get<4>();                          // Strike price
            double b = optionData.get<5>();                          // Cost of carry
            std::string optType = optionData.get<6>();               // Put or Call

            if (optType == "Call") {
                callPrice(T, sig, r, S, K, b);
            } else {
                putPrice(T, sig, r, S, K, b);
            }
            return optionPrice;
        }
    }
}
