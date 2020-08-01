/**********************************************************************************************************************
 * Function definitions for EuropeanOption.hpp
 *
 * Derived from Instrument
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "EuropeanOption.hpp"
#include "RNG.hpp"

namespace MJL {
    namespace Instrument {

        /**
         * Initialize a new EuropeanOption
         * @throws OutOfMemoryError Indicates insufficient memory for this EuropeanOption
         */
        template<typename RNG_>
        EuropeanOption<RNG_>::EuropeanOption() : T(0.25), sig(0.3), r(0.08), S(60), K(65), b(r), optType("Call") {}

        /**
         * Initialize a new EuropeanOption with the source object
         * @param source The source object used to initialize this EuropeanOptions data members
         * @throws OutOfMemoryError Indicates insufficient memory for this EuropeanOption
         */
        template<typename RNG_>
        EuropeanOption<RNG_>::EuropeanOption(const EuropeanOption &source) : T(source.T), sig(source.sig), r(source.r),
                                                    S(source.S), K(source.K), b(source.b), optType(source.optType){}

        /**
         * Destroy this EuropeanOption
         */
        template<typename RNG_>
        EuropeanOption<RNG_>::~EuropeanOption() {}

        /**
         * Create a deep copy of the source
         * @param source A EuropeanOption that will be deeply copied
         * @return A deep copy of the source
         */
        template<typename RNG_>
        EuropeanOption<RNG_> & EuropeanOption<RNG_>::operator=(const EuropeanOption<RNG_> &source) {
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
        template<typename RNG_>
        double EuropeanOption<RNG_>::callPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const {
            double tmp = sig_ * sqrt(T_);

            double N1 = RNG_::MersenneTwister();
            double N2 = N1 - tmp;

            return (S_ * exp((b_ - r_) * T) * N1) - (K_ * exp(-r_ * T_)* N2);
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
        template<typename RNG_>
        double EuropeanOption<RNG_>::putPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const {
            double tmp = sig_ * sqrt(T_);

            double N1 = RNG_::MersenneTwister();
            double N2 = N1 - tmp;

            return (K_ * exp(-r_ * T_) * N2) - (S_ * exp((b_ - r_) * T_) * N1);
            //return (K_ * exp(-r_ * T_) * N(-d2)) - (S_ * exp((b_ - r_) * T_) * N(-d1));
        }
    }
}
