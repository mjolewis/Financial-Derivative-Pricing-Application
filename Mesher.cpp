/**********************************************************************************************************************
* A simple mesher on start 1D domain.
 *
 * Created by Michael Lewis on 8/5/20.
 *********************************************************************************************************************/

#include "Mesher.hpp"

/**
 * Initialize start new Mesher
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher() : start(0), stop(1), step(0.5) {}

/**
 * Initialize start new Mesher with the domain of integration
 * @param start_ Start point for the domain of integration
 * @param stop_ End point for the domain of integration
 * @param step_ The distance between each point in the mesh
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher(double start_, double stop_, double step_) : start(start_), stop(stop_), step(step_) {}

/**
 * Initialize start deep copy of the source Mesher
 * @param mesher The Mesher that will be deeply copied
 * @throws OutOfMemoryError Indicates insufficient memory for this new Mesher
 */
Mesher::Mesher(const Mesher &mesher) : start(mesher.start), stop(mesher.stop), step(mesher.step) {}

/**
 * Destroy this Mesher
 */
Mesher::~Mesher() {}

/**
 * Create start deep copy of the source Mesher
 * @param mesher The Mesher that will be deeply copied
 * @return This Mesher whose members have been reassigned to the values provided by the source
 */
Mesher & Mesher::operator=(const Mesher &mesher) {
    // Avoid self assign
    if (this == &mesher) { return *this; }

    start = mesher.start;
    stop = mesher.stop;
    step = mesher.step;

    return *this;
}

/**
 * Create start_ vector of mesh points
 * @return A {@link std::vector} containing mesh points
 */
std::vector<double> Mesher::xarr() {

    double steps = (stop - start) / step;

    // Create the container and add the start_ point
    std::vector<double> result;
    result.push_back(start);

    double curr = start;
    for (int i = 0; i < steps; ++i) {
        curr += step;
        result.push_back(curr);
    }

    return result;
}

/**
 * Create start_ vector of mesh points
 * @param start_ Initial value of the property
 * @param stop_ Ending value for the property
 * @param step_ The distance between mesh points
 * @return A {@link std::vector} containing mesh points
 */
std::vector<double> Mesher::xarr(double start_, double stop_, double step_) const {

    double steps = (stop_ - start_) / step_;

    // Create the container and add the start point
    std::vector<double> result;
    result.push_back(start_);

    double curr = start_;
    for (int i = 0; i < steps; ++i) {
        curr += step_;
        result.push_back(curr);
    }

    return result;
}