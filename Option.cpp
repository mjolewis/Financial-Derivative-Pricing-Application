/**********************************************************************************************************************
 * A financial instrument
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "Option.hpp"
#include "RNG.hpp"

/**
 * Initialize a new Option
 * @throws OutOfMemoryError Indicates insufficient memory for this Option
 */
Option::Option() : T(0.25), sig(0.3), r(0.08), S(60), K(65), b(r) {}

/**
 * Initialize a new Option
 * @param T_ Time to expiry
 * @param sig_ Volatility
 * @param r_ Risk free rate
 * @param S_ Current price of underlying
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @throws OutOfMemoryError Indicates insufficient memory for this Option
 */
Option::Option(double T_, double sig_, double r_, double S_, double K_, double b_) {
    T = T_;
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
}

/**
 * Initialize a new Option with the source object
 * @param source The source object used to initialize this EuropeanOptions data members
 * @throws OutOfMemoryError Indicates insufficient memory for this Option
 */
Option::Option(const Option &source) : T(source.T), sig(source.sig), r(source.r), S(source.S), K(source.K), b(source.b) {}

/**
 * Destroy this Option
 */
Option::~Option() {}

/**
 * Create a deep copy of the source
 * @param source A Option that will be deeply copied
 * @return A deep copy of the source
 */
Option &Option::operator=(const Option &source) {
    // Avoid self assign
    if (this == &source) { return *this; }

    // Call base class assignment
    Instrument::operator=(source);

    T = source.T;
    sig = source.sig;
    r = source.r;
    S = source.S;
    K = source.K;
    b = source.b;

    return *this;
}

/**
 * A mechanism to calculate the call (or put) price for a corresponding put (or call) price
 * @param optionPrice
 * @param optType_ Call or Put. The default value is a Call
 * @return The price that satisfies the put-call parity relationship
 */
double Option::putCallParity(double optionPrice, const std::string& optType_) const {
    if (optType_ == "Put" || optType_ == "put") {
        return optionPrice + S - (K * exp(-r * T));
    } else {
        return optionPrice + (K * exp(-r * T)) - S;
    }
}

/**
 * Mechanism to check if a given set of call (C) and put (P) prices satisfy parity
 * @param putPrice
 * @param callPrice
 * @return True if the relationship is satisfied. Otherwise false
 */
bool Option::putCallParity(double callPrice, double putPrice) const {
    return putCallParity(callPrice, putPrice, T, K, r, S);
}

// Getters
double Option::expiry() const { return T; }
double Option::vol() const { return sig; }
double Option::riskFree() const { return r; }
double Option::spot() const { return S; }
double Option::strike() const { return K; }
double Option::carry() const { return b; }

// Setters
void Option::setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_) {
    T = T_;
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
}

void Option::expiry(double T_) { T = T_;}
void Option::vol(double sig_) { sig = sig_; }
void Option::riskFree(double r_) { r = r_; }
void Option::spot(double S_) { S = S_; }
void Option::strike(double K_) {K = K_; }
void Option::carry(double b_) { b = b_; }

// Mechanism to check if a given set of call (C) and put (P) prices satisfy parity (tolerance = 1e-5)
bool Option::putCallParity(double C, double P, double T_, double K, double r_, double S) {
    return ((C + (K * exp(-r_ * T_))) - (P + S)) <= 1e-5;
}
