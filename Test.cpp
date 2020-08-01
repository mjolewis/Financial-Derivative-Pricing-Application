/**********************************************************************************************************************
 * Test exact solutions for one-factor European equity options and Perpetual American equity options.
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/


#include <iostream>
#include "Builder.hpp"
#include "Input.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

typedef MJL::Input::Input Input;
typedef MJL::Pricers::Pricer Pricer;
typedef MJL::Pricers::RNG RNG;

int main() {

    // Begin simulation
    std::cout << "\n--------------------------------------------------------------\n\n";
    std::cout << "\t\tBlack-Scholes Option Pricing Engine\n";
    std::cout << "\t\tAuthored By: Michael Lewis\n";
    std::cout << "\t\tStart pricing engine\n";
    std::cout << "\n--------------------------------------------------------------" << std::endl;

    MJL::Builders::Builder<Input, RNG, Pricer> Builder;
    Builder.Build();

    std::cout << "\n--------------------------------------------------------------\n\n";
    std::cout << "\t\tSimulation complete";
    std::cout << "\n--------------------------------------------------------------" << std::endl;

    return 0;
}
