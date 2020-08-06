/**********************************************************************************************************************
* A simple mesher on a 1D domain. We divide an interval into J+1 mesh points, J-1 of which are internal mesh points.
 *
 * Created by Michael Lewis on 8/5/20.
 *********************************************************************************************************************/

#include "Mesher.hpp"

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