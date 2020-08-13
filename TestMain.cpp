/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Main entry point
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#include <string>

#include "TestGroupA.hpp"
#include "TestBuilder.hpp"
#include "TestExtras.hpp"

// Comment or uncomment to toggle test cases
int main() {

    // Hard-coded test cases
    TestGroupA groupA;
    groupA.PartOne();
    groupA.PartTwo();
    groupA.PartThree();
    groupA.PartFour();

    // Test Builder Pattern, which allows the user to input option data
//    TestBuilder builderTest;
//    builderTest.PartOne();

    // Test extras
//    TestExtras extrasTest;
//    extrasTest.PartOne();
}