/**********************************************************************************************************************
 * Function declarations for Instrument.hpp
 *
 * Base class for all derivative products
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

namespace MJL {
    namespace Instrument {
        class Instrument {
        public:
            virtual double callPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const = 0;
            virtual double putPrice(double T_, double sig_, double r_, double S_, double K_, double b_) const = 0;
        };
    }
}

#endif // INSTRUMENT_HPP
