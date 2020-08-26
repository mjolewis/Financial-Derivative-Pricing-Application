/**********************************************************************************************************************
 * Utility class to generate matrices
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#include "vector"
#include <string>

#include "Matrix.hpp"

/**
 * Initialize a new Matrix
 * @throws OutOfMemoryError Indicates insufficient memory for this new Matrix
 */
Matrix::Matrix() {}

/**
 * Initialize a deep copy of the source
 * @param source A Matrix that will be deeply copied
 */
Matrix::Matrix(const Matrix &source) {}

/**
 * Destroy this Matrix
 */
Matrix::~Matrix() {}

/**
 * Deeply copy the source
 * @param source A Matrix whose member variables will be deeply copied
 * @return This Matrix whose member variables are now a deep copy of the members of source
 */
Matrix & Matrix::operator=(const Matrix &source) {
    // Avoid self assign
    if (this == &source) {return *this;}

    return *this;
}

/**
 * Create a matrix of American options. Each row will variate one parameter by a monotonically increasing amount
 * @note American options do not require b=r
 * @param mesh A mesh array
 * @param property The variate parameter, which should be represented by the variate symbol (e.g. sig, r, S, K, b)
 * @param sig Volatility
 * @param r Risk-Free Rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of Carry
 * @return A {@link std::vector<std::vector<double> > of option parameters
 */
std::vector<std::vector<double>>
Matrix::matrix(const std::vector<double>& mesh, const std::string &property, double sig, double r, double S,
               double K, double b) {

    // Create a new output container for each new matrix
    std::vector<std::vector<double>> matrix;

    // Use the mesh points to modify property by a monotonically increasing amount
    if (property == "Sig" || property == "sig" || property == "Volatility" || property == "volatility" ) {

        // Monotonically increase vol and add the new option to a new row in the matrix
        for (double sig_ : mesh) {
            matrix.push_back({sig_, r, S, K, b});
        }
    } else if (property == "R" || property == "r" || property == "Risk-free" || property == "risk-free" ) {

        // Monotonically increase risk free rate and add the new option to a new row in the matrix
        // Note that because we are using the Black-Scholes stock option model, we must maintain b != r
        for (double r_ : mesh) {
            matrix.push_back({sig, r_, S, K, b});
        }
    } else if (property == "S" || property == "s" || property == "Spot" || property == "spot" ) {

        // Monotonically increase spot price and add the new option to a new row in the matrix
        for (double S_ : mesh) {
            matrix.push_back({sig, r, S_, K, b});
        }
    } else if (property == "K" || property == "k" || property == "Strike" || property == "strike" ) {

        // Monotonically increase strike price and add the new option to a new row in the matrix
        for (double K_ : mesh) {
            matrix.push_back({sig, r, S, K_, b});
        }
    } else if (property == "B" || property == "b" || property == "Beta" || property == "beta" ) {

        // Monotonically increase beta and add the new option to a new row in the matrix
        // Note that because we are using the Black-Scholes stock option model, we must maintain b != r
        for (double b_ : mesh) {
            matrix.push_back({sig, r, S, K, b_});
        }
    }

    return matrix;
}

/**
 * Create a matrix of European options. Each row will variate one parameter by a monotonically increasing amount
 * @note European options require b=r
 * @param mesh A mesh array
 * @param property The variate parameter, which should be represented by the variate symbol (e.g. T, sig, r, S, K, b)
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-Free Rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of Carry
 * @return A {@link std::vector<std::vector<double> > of option parameters
 */
std::vector<std::vector<double>>
Matrix::matrix(const std::vector<double>& mesh, const std::string &property, double T, double sig, double r,
               double S, double K, double b) {

    // Create a new output container for each new matrix
    std::vector<std::vector<double>> matrix;

    // Use the mesh points to modify property by a monotonically increasing amount
    if (property == "T" || property == "t" || property == "Expiry" || property == "expiry") {

        // Monotonically increase expiry and add the new option to a new row in the matrix
        for (double T_ : mesh) {
            matrix.push_back({T_, sig, r, S, K, b});
        }
    } else if (property == "Sig" || property == "sig" || property == "Volatility" || property == "volatility" ) {

        // Monotonically increase vol and add the new option to a new row in the matrix
        for (double sig_ : mesh) {
            matrix.push_back({T, sig_, r, S, K, b});
        }
    } else if (property == "R" || property == "r" || property == "Risk-free" || property == "risk-free" ) {

        // Monotonically increase risk free rate and add the new option to a new row in the matrix
        // Note that because we are using the Black-Scholes stock option model, we must maintain b = r
        for (double r_ : mesh) {
            matrix.push_back({T, sig, r_, S, K, r_});
        }
    } else if (property == "S" || property == "s" || property == "Spot" || property == "spot" ) {

        // Monotonically increase spot price and add the new option to a new row in the matrix
        for (double S_ : mesh) {
            matrix.push_back({T, sig, r, S_, K, b});
        }
    } else if (property == "K" || property == "k" || property == "Strike" || property == "strike" ) {

        // Monotonically increase strike price and add the new option to a new row in the matrix
        for (double K_ : mesh) {
            matrix.push_back({T, sig, r, S, K_, b});
        }
    } else if (property == "B" || property == "b" || property == "Beta" || property == "beta" ) {

        // Monotonically increase beta and add the new option to a new row in the matrix
        // Note that because we are using the Black-Scholes stock option model, we must maintain b = r
        for (double b_ : mesh) {
            matrix.push_back({T, sig, b_, S, K, b_});
        }
    }

    return matrix;
}

/**
 * Create a matrix of futures. Each row will variate one parameter by a monotonically increasing amount
 * @note The Black-Scholes futures options model requires b=0
 * @param mesh A mesh array
 * @param property The variate parameter, which should be represented by the variate symbol (e.g. T, sig, r, S, K, b)
 * @param T Expiry
 * @param sig Volatility
 * @param r Risk-Free Rate
 * @param S Spot price
 * @param K Strike price
 * @param b Cost of Carry
 * @return A {@link std::vector<std::vector<double> > of option parameters
 */
std::vector<std::vector<double>>
Matrix::futuresMatrix(const std::vector<double>& mesh, const std::string &property, double T, double sig, double r,
                      double S, double K, double b) {

    // Create a new output container for each new matrix
    std::vector<std::vector<double>> matrix;

    // Use the mesh points to modify property by a monotonically increasing amount
    if (property == "T" || property == "t" || property == "Expiry" || property == "expiry") {

        // Monotonically increase expiry and add the new option to a new row in the matrix
        for (double T_ : mesh) {
            matrix.push_back({T_, sig, r, S, K, 0});
        }
    } else if (property == "Sig" || property == "sig" || property == "Volatility" || property == "volatility" ) {

        // Monotonically increase vol and add the new option to a new row in the matrix
        for (double sig_ : mesh) {
            matrix.push_back({T, sig_, r, S, K, 0});
        }
    } else if (property == "R" || property == "r" || property == "Risk-free" || property == "risk-free" ) {

        // Monotonically increase risk free rate and add the new option to a new row in the matrix
        for (double r_ : mesh) {
            matrix.push_back({T, sig, r_, S, K, 0});
        }
    } else if (property == "S" || property == "s" || property == "Spot" || property == "spot" ) {

        // Monotonically increase spot price and add the new option to a new row in the matrix
        for (double S_ : mesh) {
            matrix.push_back({T, sig, r, S_, K, 0});
        }
    } else if (property == "K" || property == "k" || property == "Strike" || property == "strike" ) {

        // Monotonically increase strike price and add the new option to a new row in the matrix
        for (double K_ : mesh) {
            matrix.push_back({T, sig, r, S, K_, 0});
        }
    } else if (property == "B" || property == "b" || property == "Beta" || property == "beta" ) {

        // Monotonically increase beta and add the new option to a new row in the matrix
        for (double b_ : mesh) {
            matrix.push_back({T, sig, r, S, K, 0});
        }
    }

    return matrix;
}
