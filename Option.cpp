/**********************************************************************************************************************
 * European equity option
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#include "Option.hpp"
#include "RNG.hpp"

/**
 * Initialize a new Option
 * @throws OutOfMemoryError Indicates insufficient memory for this Option
 */
Option::Option() : T(0.25), sig(0.3), r(0.08), S(60), K(65), b(r), optType("Call"), optFlavor("European"), uName("Default") {}

Option::Option(double T_, double sig_, double r_, double S_, double K_, double b_, std::string& optType_, std::string& optFlavor_, std::string& uName_) {
    T = T_;
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
    optType = optType_;
    optFlavor = optFlavor_;
    uName = uName_;
}

/**
 * Initialize a new Option with the source object
 * @param source The source object used to initialize this EuropeanOptions data members
 * @throws OutOfMemoryError Indicates insufficient memory for this Option
 */
Option::Option(const Option &source) : T(source.T), sig(source.sig), r(source.r), S(source.S), K(source.K), b(source.b),
                                       optType(source.optType), optFlavor(source.optFlavor), uName(source.uName) {}

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
    optType = source.optType;
    optFlavor = source.optFlavor;
    uName = source.uName;

    return *this;
}

double Option::expiry() const { return T; }
double Option::vol() const { return sig; }
double Option::riskFree() const { return r; }
double Option::spot() const { return S; }
double Option::strike() const { return K; }
double Option::carry() const { return b; }
const std::string & Option::type() const { return optType; }
const std::string & Option::flavor() const { return optFlavor; }
const std::string & Option::underlying() const { return uName; }
