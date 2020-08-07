/**********************************************************************************************************************
* A simple mesher on a 1D domain. We divide an interval into J+1 mesh points, J-1 of which are internal mesh points.
 *
 * Created by Michael Lewis on 8/5/20.
 *********************************************************************************************************************/

#include <string>
#include <iostream>

#include "Mesher.hpp"
#include "Option.hpp"

/**
 * Initialize a new Mesher
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher() : a(0), b(1) {}

/**
 * Initialize a new Mesher with the domain of integration
 * @param A Start point for the domain of integration
 * @param B End point for the domain of integration
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher(double A, double B) : a(A), b(B) {}

/**
 * Initialize a deep copy of the source Mesher
 * @param mesher The Mesher that will be deeply copied
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher(const Mesher &mesher) : a(mesher.a), b(mesher.b) {}

/**
 * Destroy this Mesher
 */
Mesher::~Mesher() {}

/**
 * Create a deep copy of the source Mesher
 * @param mesher The Mesher that will be deeply copied
 * @return This Mesher whose members have been reassigned to the values provided by the source
 */
Mesher & Mesher::operator=(const Mesher &mesher) {
    // Avoid self assign
    if (this == &mesher) { return *this; }

    a = mesher.a;
    b = mesher.b;

    return *this;
}

/**
 * Create a vector of mesh points, which can be used when simulating option prices
 * @param J The factor used to determine the distance between mesh points
 * @return A {@link std::vector} containing mesh points
 */
std::vector<double> Mesher::xarr(int J) const {
    double h = (b - a) / double (J);

    int size = J;
    int start = 1;

    std::vector<double> result(size, start);
    result[0] = a;
    result[J - 1] = b;

    for (unsigned int j = 1; j < size; ++j) {
        result[j] = result[j - 1] + h;
    }

    return result;
}

/**
 * Create a vector of mesh points, which can be used when simulating option prices
 * @param a_ Domain of integration minimum value
 * @param b_ Domain of integration maximum value
 * @param J The factor used to determine the distance between mesh points
 * @return A {@link std::vector} containing mesh points
 */
std::vector<double> Mesher::xarr(double a_, double b_, int J) const {
    double h = (b_ - a_) / double (J);

    int size = J;
    int start = 1;

    std::vector<double> result(size, start);
    result[0] = a_;
    result[J - 1] = b_;

    for (unsigned int j = 1; j < size; ++j) {
        result[j] = result[j - 1] + h;
    }

    return result;
}

/**
 * Create a matrix of option parameters. Each row will variate one parameter by a monotonically increasing amount
 * @param a_ Domain of integration minimum value
 * @param b_ Domain of integration maximum value
 * @param J The factor used to determine the distance between mesh points
 * @param optionData The initial option parameters
 * @param property The variate parameter, which should be represented by the variate symbol (e.g. T, sig, r, S, K, b)
 * @return A {@link std::vector<std::vector<double> > of option parameters
 */
std::vector<std::vector<double> >Mesher::getMatrix(double a_, double b_, int J, const Option& option, const std::string& property) {

    // Create the output matrix
    std::vector<std::vector<double> > matrix;

    // Add the initial option data to the inner vector using C++98
    std::vector<double> rowZero;
    rowZero.push_back(option.expiry());
    rowZero.push_back(option.vol()),
    rowZero.push_back(option.riskFree());
    rowZero.push_back(option.spot());
    rowZero.push_back(option.strike());
    rowZero.push_back(option.carry());

    // Add the inner vector to the first row of the matrix
    matrix.push_back(rowZero);


    // Generate mesh points
    std::vector<double> meshPoints = xarr(a_, b_, J);

    // Use the mesh points to modify property by a monotonically increasing amount
    if (property == "T" || property == "t" || property == "Expiry" || property == "expiry") {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase expiry and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry() + meshPoints[i]);
            row.push_back(option.vol()),
            row.push_back(option.riskFree());
            row.push_back(option.spot());
            row.push_back(option.strike());
            row.push_back(option.carry());

            matrix.push_back(row);
        }
    } else if (property == "Sig" || property == "sig" || property == "Volatility" || property == "volatility" ) {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase vol and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry());
            row.push_back(option.vol() + meshPoints[i]),
            row.push_back(option.riskFree());
            row.push_back(option.spot());
            row.push_back(option.strike());
            row.push_back(option.carry());

            matrix.push_back(row);
        }
    } else if (property == "R" || property == "r" || property == "Risk-free" || property == "risk-free" ) {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase risk free rate and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry());
            row.push_back(option.vol()),
            row.push_back(option.riskFree() + meshPoints[i]);
            row.push_back(option.spot());
            row.push_back(option.strike());
            row.push_back(option.carry());

            matrix.push_back(row);
        }
    } else if (property == "S" || property == "s" || property == "Spot" || property == "spot" ) {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase spot price and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry());
            row.push_back(option.vol()),
            row.push_back(option.riskFree());
            row.push_back(option.spot() + meshPoints[i]);
            row.push_back(option.strike());
            row.push_back(option.carry());

            matrix.push_back(row);
        }
    } else if (property == "K" || property == "k" || property == "Strike" || property == "strike" ) {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase strike price and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry());
            row.push_back(option.vol()),
            row.push_back(option.riskFree());
            row.push_back(option.spot());
            row.push_back(option.strike() + meshPoints[i]);
            row.push_back(option.carry());

            matrix.push_back(row);
        }
    } else if (property == "B" || property == "b" || property == "Beta" || property == "beta" ) {
        for (int i = 1; i < meshPoints.size(); ++i) {

            // Monotonically increase beta and add the new option to a new row in the matrix
            std::vector<double> row;
            row.push_back(option.expiry());
            row.push_back(option.vol()),
            row.push_back(option.riskFree());
            row.push_back(option.spot());
            row.push_back(option.strike());
            row.push_back(option.carry() + meshPoints[i]);

            matrix.push_back(row);
        }
    }

    return matrix;
}