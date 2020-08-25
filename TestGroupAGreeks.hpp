/**********************************************************************************************************************
 * Black-Scholes Option EuropeanOption - Group A
 *
 * Created by Michael Lewis on 8/2/20.
 *********************************************************************************************************************/

#ifndef TESTGROUPAGREEKS_HPP
#define TESTGROUPAGREEKS_HPP

#include <iostream>
#include <iomanip>

#include "Matrix.hpp"
#include "Mesher.hpp"
#include "Output.hpp"
#include "EuropeanOption.hpp"
#include "RNG.hpp"

class TestGroupAGreeks {
private:
private:
    EuropeanOption<Mesher, Matrix, RNG, Output> option = EuropeanOption<Mesher, Matrix, RNG, Output>(0.5, 0.36, 0.1, 105, 100, 0);

    Mesher mesher;                                              // Meshing engine
    Matrix matrix;                                              // Matrix engine

public:
    TestGroupAGreeks() {};
    virtual ~TestGroupAGreeks() {};

    void PartOne() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part A\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::vector<std::vector<double>> prices = option.delta();
        std::cout << "\nExpiry: " << option.expiry()
                  << "\nVolatility: " << option.vol()
                  << "\nRisk-free rate: " << option.riskFree()
                  << "\nStock price: " << option.spot()
                  << "\nStrike price: " << option.strike()
                  << "\nCost of carry: " << option.carry() << "\n"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";

        for (const auto& row : prices) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << row[0]
                      << std::setw(15) << row[1] << "\n";
        }

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part A\n";
        std::cout << "\n*******************************************************************" << std::endl;
    }

    void PartTwoAndThree() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part B and C\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        std::vector<double> mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = Matrix::futuresMatrix(mesh,"S", option.expiry(),
                option.vol(), option.riskFree(), option.spot(), option.strike(), option.carry());
        std::vector<std::vector<double>> prices = option.delta(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nExact solution for Call and Put Delta as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        std::vector<double> gamma = option.gamma(options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\nExact solution for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << gamma[i] << "\n";
        }

        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part B and C\n";
        std::cout << "\n*******************************************************************" << std::endl;
    };

    void PartFour() {

        // Begin simulation
        std::cout << "\n*******************************************************************\n\n";
        std::cout << "Black-Scholes Option Pricing Engine\n";
        std::cout << "Test Batch: Group A Greeks Part D\n";
        std::cout << "Authored By: Michael Lewis\n";
        std::cout << "\n*******************************************************************" << std::endl;

        // FDM for monotonically increasing Spot
        std::vector<double> mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        std::vector<std::vector<double>> options = Matrix::futuresMatrix(mesh, "S", option.expiry(),
                option.vol(), option.riskFree(), option.spot(), option.strike(), option.carry());
        std::vector<std::vector<double>> prices = option.delta(.1, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = 0.1:"
                  << "\nFDM approximation for Call and Put Delta for a monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        std::vector<double> gamma = option.gamma(.1, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = 0.1:"
                  << "\nFDM approximation for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << gamma[i] << "\n";
        }

        // FDM for monotonically increasing Spot
        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        prices = option.delta(.5, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = .5:"
                  << "\nFDM approximation for Call and Put Delta for a monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        gamma = option.gamma(.5, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = 0.5:"
                  << "\nFDM approximation for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << gamma[i] << "\n";
        }

        // FDM for monotonically increasing Spot
        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        prices = option.delta(2, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = 2:"
                  << "\nFDM approximation for Call and Put Delta for a monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Call Delta"
                  << std::setw(15) << "Put Delta\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << prices[i][0]
                      << std::setw(15) << prices[i][1] << "\n";
        }

        mesh = mesher.xarr(option.spot(), option.spot() + 5, 0.5);
        options = Matrix::futuresMatrix(mesh, "S", option.expiry(),option.vol(), option.riskFree(),
                option.spot(), option.strike(), option.carry());
        gamma = option.gamma(2, options);

        // Iterate through the matrix and print the option prices and sensitivities
        std::cout << "\n\nh = 2:"
                  << "\nFDM approximation for Gamma as a function of monotonically increasing Spot:\n"
                  << std::setw(15) << "Spot Price"
                  << std::setw(15) << "Gamma\n"
                  << std::setw(15) << "-----------"
                  << std::setw(15) << "-----------\n";
        for (int i = 0; i < options.size(); ++i) {
            std::cout << std::setprecision(7)
                      << std::setw(15) << mesh[i]
                      << std::setw(15) << gamma[i] << "\n";
        }


        std::cout << "\n\n*******************************************************************\n\n";
        std::cout << "Completed Group A Greeks Part D\n";
        std::cout << "\n*******************************************************************" << std::endl;
    };

};

#endif //TESTGROUPAGREEKS_HPP
