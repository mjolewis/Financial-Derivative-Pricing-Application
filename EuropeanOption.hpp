/**********************************************************************************************************************
 * Function declarations for EuropeanOption.hpp
 *
 * Derived from Instrument
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef EUROPEANOPTION_HPP
#define EUROPEANOPTION_HPP

#include "string"

#include "Instrument.hpp"

namespace MJL {
    namespace Instrument {
        class EuropeanOption : public Instrument {
        private:

            // Required option data
            double T;                           // Expiry time/maturity. E.g. T = 1 means one year
            double sig;                         // Volatility
            double r;                           // Risk-free interest rate
            double S;                           // Spot price
            double K;                           // Strike price
            double b;                           // Cost of carry; b = r for Black-Scholes equity option model
            std::string optType;                // Call or Put

        public:

            // Constructors and Destructors
            EuropeanOption();
            EuropeanOption(const EuropeanOption& source);
            virtual ~EuropeanOption();

            // Operator overloading
            EuropeanOption& operator=(const EuropeanOption& source);

            // Base class function implementations
            double callPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const;
            double putPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const;

        };
    }
}


#endif //EUROPEANOPTION_HPP
