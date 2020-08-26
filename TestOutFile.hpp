/**********************************************************************************************************************
 * Black-Scholes Option EuropeanOption - Output option data to a CSV file
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTOUTFILE_HPP
#define TESTOUTFILE_HPP

#include <iostream>
#include <iomanip>

#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Output.hpp"
#include "AmericanOption.hpp"
#include "EuropeanOption.hpp"
#include "RNG.hpp"

class TestOutFile {
private:

    // Perpetual price is the time-homogenous price and is the same as the normal price when the expiry price T tends to infinity
    EuropeanOption<Mesher, Matrix, RNG, Output> europeanOption = EuropeanOption<Mesher, Matrix, RNG, Output>(0.25, 0.3, 0.08, 60, 65, 0.08);
    AmericanOption<Mesher, Matrix, Output> americanOption = AmericanOption<Mesher, Matrix, Output>(0.1, 0.1, 110, 100, 0.02);

public:
    TestOutFile() {};

    virtual ~TestOutFile() {};

    void send() {

        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test .csv output\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        europeanOption.price(0.1, europeanOption.spot(), europeanOption.spot() + 10, 0.5, "S");
        americanOption.price(americanOption.spot(), americanOption.spot() + 10, 0.5, "S");

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Simulation - Check for OptionData.csv\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTOUTFILE_HPP
