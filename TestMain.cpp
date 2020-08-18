/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Main entry point
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/


#include "Builder.hpp"

// Comment or uncomment to toggle test cases
int main() {

    Builder<Input, RNG, Output, Pricer> Builder;

    //Builder.BuildConsoleInterface();
    Builder.BuildGroupAPricing();
    Builder.BuildGroupAGreeks();
    Builder.BuildGroupB();

    // Test extras
//    TestExtras extrasTest;
//    extrasTest.PartB();
}