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
            virtual void print() const = 0;
        };
    }
}

#endif // INSTRUMENT_HPP
