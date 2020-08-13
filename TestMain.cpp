/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Main entry point
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#include <string>

#include "TestGroupAPricing.hpp"
#include "TestGroupAGreeks.hpp"
#include "TestBuilder.hpp"
#include "TestExtras.hpp"

// Comment or uncomment to toggle test cases
int main() {

    // Group A Pricing Tests
    TestGroupAPricing groupAPricing;
    groupAPricing.PartOne();
    groupAPricing.PartTwo();
    groupAPricing.PartThree();
    groupAPricing.PartFour();

    // Group A Greeks Tests;
    TestGroupAGreeks groupAGreeks;
    groupAGreeks.PartOne();

    // Test Builder Pattern, which allows the user to input option data
//    TestBuilder builderTest;
//    builderTest.PartOne();

    // Test extras
//    TestExtras extrasTest;
//    extrasTest.PartOne();
}