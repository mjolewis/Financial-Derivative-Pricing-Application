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
 * Provide a console interface to dynamically get the output file
 * @param value The price of an Option
 */
void Output::sendToFile(double value) const {
    std::ofstream outFile;                       // Object for writing to a file
    std::string fileName;
    std::cout << "Enter output location data: ";
    std::cin >> fileName;

    outFile.open(fileName);
    if (outFile.is_open()) {
        outFile << value;
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
void Output::sendToFile(const std::vector<double> meshPoints, const std::vector<std::vector<double> > &prices,
        const std::vector<std::vector<double> > &deltas) const {

    std::ofstream outFile;                       // Object for writing to a file
    std::string fileName;

    outFile.open("OptionData.csv");
    if (outFile.is_open()) {
        outFile << "Mesh Points" << "," << "Price" << "," << "Delta" << "," << "Gamma" << std::endl;
        for (int i = 0; i < prices.size(); ++i) {
            outFile << meshPoints[i] << "," << prices[i][0] << "," << deltas[i][0] << "," << std::endl; // gammas[i][0] << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Unable to open the file. Check filepath permissions\n";
    }
}