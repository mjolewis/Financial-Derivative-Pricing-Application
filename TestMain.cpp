/**********************************************************************************************************************
 * Black-Scholes Option EuropeanOption - Main entry point
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#include "TestGroupAPricing.hpp"
#include "TestGroupAGreeks.hpp"
#include "TestGroupB.hpp"
#include "TestExtras.hpp"
#include "TestOutFile.hpp"
#include <chrono>

// Comment or uncomment to toggle test cases
int main() {

    // Group A Pricing Tests
//    TestGroupAPricing groupAPricing;
//    groupAPricing.PartOne();
//    groupAPricing.PartTwo();
//    groupAPricing.PartThree();
//    groupAPricing.PartFour();

    // Group A Greeks Tests;
//    TestGroupAGreeks groupAGreeks;
//    groupAGreeks.PartOne();
//    groupAGreeks.PartTwoAndThree();
//    groupAGreeks.PartFour();

    // Group B Pricing Tests
//    TestGroupB groupB;
//    groupB.PartB();
//    groupB.PartCAndD();

    auto start = std::chrono::steady_clock::now();
    // Test output file
    TestOutFile outfile;
    outfile.send();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = end - start;
    std::cout << "elapsed time: " << elapsedTime.count() << std::endl;

    // Test extras
//    TestExtras extrasTest;
//    extrasTest.PartB();
}