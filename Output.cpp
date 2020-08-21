/**********************************************************************************************************************
 * Black-Scholes Option pricing application - Output class
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>

#include "Output.hpp"

/**
 * Initialize a new Output object
 * @throws OutOfMemoryError Indicates insufficient memory for this new Output
 */
Output::Output() {}

/**
 * Initialize a new Output object
 * @param source An output object whose members will be used to initialize this new Output
 * @throws OutOfMemoryError Indicates insufficent memory for this new Output
 */
Output::Output(const Output &source) {}

/**
 * Destroy this Output
 */
Output::~Output() {}

/**
 * Deeply copy the source
 * @param source An Output object whose members will be deeply copied into this Output object
 * @return This Output object whose members are now a deep copy of the source members
 */
Output & Output::operator=(const Output &source) {
    // Avoid self assign
    if (this == &source) {return *this;}

    return *this;
}

/**
 * Send option data to OptionData.csv
 * @param matrix A prices of Option prices
 * @param deltas A matrix of Option deltas
 */
void Output::csv(const std::vector<double>& meshPoints, const std::vector<std::vector<double> > &prices,
                 const std::vector<std::vector<double> > &deltas) const {

    std::ofstream outFile;                       // Object for writing to a file

    outFile.open("OptionData.csv");
    if (outFile.is_open()) {
        outFile << "Mesh Points" << "," << "Call Price" << "," << "Put Price" << "," << "Call Delta" << ","
                << "Put Delta"<< std::endl;
        for (int i = 0; i < prices.size(); ++i) {
            outFile << meshPoints[i] << "," << prices[i][0] << "," << prices[i][1] << "," << deltas[i][0] << ","
                    << deltas[i][1] << "," << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Unable to open the file. Check filepath permissions\n";
    }
}

/**
 * Send option data to OptionData.csv
 * @param matrix A prices of Option prices
 * @param deltas A matrix of Option deltas
 * @param gammas A matrix of Option gammas
 */
void Output::csv(const std::vector<double>& meshPoints, const std::vector<std::vector<double> > &prices,
                 const std::vector<std::vector<double> > &deltas, const std::vector<double>& gammas) const {

    std::ofstream outFile;                       // Object for writing to a file

    outFile.open("OptionData.csv");
    if (outFile.is_open()) {
        outFile << "Mesh Points" << "," << "Call Price" << "," << "Put Price" << "," << "Call Delta" << ","
                << "Put Delta"<< "," << "Gamma" << std::endl;
        for (int i = 0; i < prices.size(); ++i) {
            outFile << meshPoints[i] << "," << prices[i][0] << "," << prices[i][1] << "," << deltas[i][0] << ","
                    << deltas[i][1] << "," << gammas[i] << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Unable to open the file. Check filepath permissions\n";
    }
}