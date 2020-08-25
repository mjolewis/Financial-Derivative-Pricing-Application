/**********************************************************************************************************************
 * A financial instrument with expiry T approaching infinity
 *
 * @note A host class for Mesher, Matrix, and Output policies
 *
 * Created by Michael Lewis on 8/22/20.
 *********************************************************************************************************************/

#ifndef AMERICANOPTION_HPP
#define AMERICANOPTION_HPP

#include "vector"
#include "Mesher.hpp"
#include "Matrix.hpp"
#include "Output.hpp"

template<typename Mesher_, typename Matrix_, typename Output_>
class AmericanOption : public Mesher_, public Matrix_, public Output_ {
private:
    // Required option data
    double sig;                                  // Volatility
    double r;                                    // Risk-free interest rate
    double S;                                    // Spot price
    double K;                                    // Strike price
    double b;                                    // Cost of carry

    // Helper function
    std::vector<std::vector<double>> price(double sig_, double r_, double S_, double K_, double b_) const;

public:
    // Constructors and Destructors
    AmericanOption();
    AmericanOption(const AmericanOption& source);
    AmericanOption(double sig_, double r_, double S_, double K_, double b_);
    virtual ~AmericanOption();

    // Overloaded operators
    AmericanOption& operator=(const AmericanOption& source);

    // Core pricing functionality
    std::vector<std::vector<double>> price() const;
    void price(double start, double stop, double step, const std::string& property) const;
    std::vector<std::vector<double>> price(const std::vector<std::vector<double> >& matrix) const;

    // Accessors
    double vol() const;
    double riskFree() const;
    double spot() const;
    double strike() const;
    double carry() const;

    // Mutators
    void setOptionData(double sig_, double r_, double S_, double K_, double b_);
    void vol(double sig_);
    void riskFree(double r_);
    void spot(double S_);
    void strike(double K_);
    void carry(double b_);
};

#ifndef AMERICANOPTION_CPP
#include "AmericanOption.cpp"

#endif // AMERICANOPTION_CPP
#endif // AMERICANOPTION_HPP
