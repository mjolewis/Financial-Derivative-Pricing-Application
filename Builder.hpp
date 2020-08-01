/**********************************************************************************************************************
 * Builder design pattern used to centralize the build and assembly
 *
 * Created by Michael Lewis on 7/31/20.
 *********************************************************************************************************************/

#ifndef BUILDER_HPP
#define BUILDER_HPP

template<typename Input_, typename RNG_, typename Pricer_>
class Builder : public Input_, public RNG_, public Pricer_ {
private:
public:
    Builder();

    virtual ~Builder();

    void Build();

    void Finished();
};

#ifndef Builder_CPP
#include "Builder.cpp"

#endif // Builder_CPP
#endif //BUILDER_HPP
