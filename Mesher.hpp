/**********************************************************************************************************************
* A simple mesher on a 1D domain. We divide an interval into J+1 mesh points, J-1 of which are internal mesh points.
 *
 * Created by Michael Lewis on 8/5/20.
 *********************************************************************************************************************/

#ifndef MESHER_HPP
#define MESHER_HPP

#include <vector>

class Mesher {
private:
    double a, b;                                      // Interval
public:
    Mesher();
    Mesher(double A, double B);                       // Domain of integration
    Mesher(const Mesher& mesher);
    virtual ~Mesher();

    Mesher& operator=(const Mesher& mesher);

    std::vector<double> xarr(int J) const;            // Vector of mesh points
};


#endif // MESHER_HPP
