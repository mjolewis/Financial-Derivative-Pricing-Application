/**********************************************************************************************************************
 * Black-Scholes Option Pricer - Output option data to a CSV file
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTOUTFILE_HPP
#define TESTOUTFILE_HPP

#include <iostream>
#include <iomanip>

#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Option.hpp"
#include "Output.hpp"
#include "Pricer.hpp"
#include "RNG.hpp"

class TestOutFile {
private:

    // Perpetual price is the time-homogenous price and is the same as the normal price when the expiry price T tends to infinity
    Option europeanOption = Option(0.25, 0.3, 0.08, 60, 65, 0.08);
    Option americanOption = Option(std::numeric_limits<double>::infinity(), 0.1, 0.1, 110, 100, 0.02);

    Pricer<Mesher, Matrix, RNG, Output> pricer;                 // Pricing engine
public:
    TestOutFile() {};

    virtual ~TestOutFile() {};

    void send() {

        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test .csv output\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        pricer.priceEuropean(0.1, europeanOption.spot(), europeanOption.spot() + 10, 0.5, europeanOption, "S");
        pricer.priceAmerican(0.1, americanOption.spot(), americanOption.spot() + 10, 0.5, americanOption, "S");

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Simulation - Check for OptionData.csv\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }
};

#endif // TESTOUTFILE_HPP
