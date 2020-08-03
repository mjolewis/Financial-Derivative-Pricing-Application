/**********************************************************************************************************************
 * Base class for all derivative products
 *
 * Created by Michael Lewis on 8/3/20.
 *********************************************************************************************************************/

#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

class Instrument {
public:
    Instrument() {};
    Instrument(const Instrument& source) {};
    virtual ~Instrument() {};

    Instrument& operator=(const Instrument& source) { return *this; };
};


#endif // INSTRUMENT_HPP
