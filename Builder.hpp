/**********************************************************************************************************************
 * Builder design pattern used to centralize the build and assembly
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_HPP
#define BUILDER_HPP

template<class Input_, class RNG_, class Instrument_,
template<class , class, class> class Pricer_>
class Builder : public Pricer_<Input_, RNG_, Instrument_> {
private:
public:

    // Constructors and Destructors
    Builder();
    virtual ~Builder();

    // Core functionality
    void Build();
    void Finished();
};

#ifndef Builder_CPP
#include "Builder.cpp"

#endif // Builder_CPP
#endif // BUILDER_HPP
