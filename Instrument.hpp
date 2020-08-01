/**********************************************************************************************************************
 * Function declarations for Instrument.hpp
 *
 * Base class for all derivative products
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

class Instrument {
public:

    Instrument();

    Instrument(const Instrument &source);

    virtual ~Instrument();

    Instrument &operator=(const Instrument &source);

    virtual double callPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const = 0;

    virtual double putPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const = 0;
};

#endif // INSTRUMENT_HPP
