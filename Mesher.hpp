/**********************************************************************************************************************
* A simple mesher on start 1D domain.
 *
 * Created by Michael Lewis on 8/5/20.
 *********************************************************************************************************************/

#ifndef MESHER_HPP
#define MESHER_HPP

#include <vector>

#include "Option.hpp"

class Mesher {
private:
    double start, stop, step;                                        // Interval and step size
public:
    Mesher();
    Mesher(double start_, double stop_, double step_);               // Domain of integration
    Mesher(const Mesher& mesher);
    virtual ~Mesher();

    Mesher& operator=(const Mesher& mesher);

    // Vectors of mesh points
    std::vector<double> xarr();
    std::vector<double> xarr(double start_, double stop_, double step_) const;
};

#endif // MESHER_HPP
