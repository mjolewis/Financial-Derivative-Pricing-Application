/**********************************************************************************************************************
 * Black-Scholes Option Pricer
 *
 * Main entry point, which manages multiple test files
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#include "TestBatches.hpp"
#include "TestBuilder.hpp"

int main() {

    // Hard-coded test cases
//    TestBS batchTests;
//    batchTests.RunTest();

    // Test Builder Pattern, which allows the user to input option data
    TestBuilder builderTest;
    builderTest.RunTest();
}