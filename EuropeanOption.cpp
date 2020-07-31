/**********************************************************************************************************************
 * Function definitions for EuropeanOption.hpp
 *
 * Derived from Instrument
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "EuropeanOption.hpp"

namespace MJL {
    namespace Instrument {

        /**
         * Initialize a new EuropeanOption
         * @throws OutOfMemoryError Indicates insufficient memory for this EuropeanOption
         */
        EuropeanOption::EuropeanOption() {}

        /**
         * Initialize a new EuropeanOption with the source object
         * @param source The source object used to initialize this EuropeanOptions data members
         * @throws OutOfMemoryError Indicates insufficient memory for this EuropeanOption
         */
        EuropeanOption::EuropeanOption(const EuropeanOption &source) : T(source.T), sig(source.sig), r(source.r),
                                                    S(source.S), K(source.K), b(source.b), optType(source.optType){}

        /**
         * Destroy this EuropeanOption
         */
        EuropeanOption::~EuropeanOption() {}

        /**
         * Create a deep copy of the source
         * @param source A EuropeanOption that will be deeply copied
         * @return A deep copy of the source
         */
        EuropeanOption & EuropeanOption::operator=(const EuropeanOption &source) {
            // Avoid self assign
            if (this == &source) { return *this; }

            T = source.T;
            sig = source.sig;
            r = source.r;
            S = source.S;
            K = source.K;
            b = source.b;
            optType = source.optType;

            return *this;
        }

        /**
         * Calculates the call price using the Black-Scholes formula
         * @param T_ Expiry
         * @param sig_ Volatility
         * @param r_ Risk-free rate
         * @param S_ Price of underlying
         * @param K_ String price
         * @param b_ Cost of carry
         * @return The call option price
         */
        double EuropeanOption::callPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const {
            double tmp = sig_ * sqrt(T_);

            double d1 = (log(S_/K_) + (b_ + (sig_ * sig_) * 0.5 ) * T_) / tmp;
            double d2 = d1 - tmp;


            return (S_ * exp((b_ - r_) * T) * N(d1)) - (K_ * exp(-r_ * T_)* N(d2));
        }

        /**
         * Calculates the put price using the Black-Scholes formula
         * @param T_ Expiry
         * @param sig_ Volatility
         * @param r_ Risk-free rate
         * @param S_ Price of underlying
         * @param K_ String price
         * @param b_ Cost of carry
         * @return The put option price
         */
        double EuropeanOption::putPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const {
            double tmp = sig_ * sqrt(T_);
            double d1 = ( log(S_/K_) + (b_ + (sig_ * sig_) * 0.5) * T_)/ tmp;
            double d2 = d1 - tmp;

            return (K_ * exp(-r_ * T_) * N(-d2)) - (S_ * exp((b_ - r_) * T_) * N(-d1));
        }
    }
}
