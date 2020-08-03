/**********************************************************************************************************************
 * Builder design pattern used to centralize the build and assembly of the Black-Scholes Option Pricer
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_HPP
#define BUILDER_HPP

template<typename Input_, typename RNG_, typename Instrument_,
template<typename, typename, typename> class Pricer_>
class Builder : public Pricer_<Input_, RNG_, Instrument_> {
public:
    // Constructors and Destructors
    Builder();
    Builder(const Builder& builder);
    virtual ~Builder();

    Builder& operator=(const Builder& builder);

    // Core functionality
    void Build();
};

#ifndef BUILDER_CPP
#include "Builder.cpp"

#endif // BUILDER_CPP
#endif // BUILDER_HPP
