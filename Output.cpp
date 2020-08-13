/**********************************************************************************************************************
 * Black-Scholes Option pricing application - Output class
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#include <fstream>
#include <ios>

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
 * @return This Output object whose members are now a deepy copy of the source members
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
 * Provide a console interface to dynamically get the output file
 * @param matrix A matrix of Option prices
 */
void Output::sendToFile(const std::vector<std::vector<double> > &matrix) const {
    std::ofstream outFile;                       // Object for writing to a file
    std::string fileName;
    std::cout << "Enter output location data: ";
    std::cin >> fileName;

    outFile.open(fileName);
    if (outFile.is_open()) {
        for (auto &row : matrix) {
            outFile << row[0] << "\n";
        }
        outFile.close();
    } else {
        std::cout << "Unable to open the file. Check filepath permissions\n";
    }
}