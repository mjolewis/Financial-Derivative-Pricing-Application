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
 * @param value
 */
void Output::sendToFile(double value) {
    std::string fileName;
    std::cout << "Enter output location data:\n";

    try {
        std::cout << "Fully qualified path and filename:\n";
        std::cin >> fileName;

        // Handle input errors and crashes gracefully
        if (!std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default value to /Users/Black-Scholes Option Data.xlsx";
            fileName = "/Users/Black-Scholes Option Data.xlsx";
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    // Write to the file
    try {
        outFile.open(fileName, std::ios::out);

        // Handle file opening errors
        if (!outFile) {
            std::cout << "Unable to open the file. Check filepath permissions\n";
        } else {
            outFile << value;                    // Write to the file
            outFile.close();                     // Close file to clean up resources
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

/**
 * Provide a console interface to dynamically get the output file
 * @param matrix
 */
void Output::sendToFile(const std::vector<std::vector<double> > &matrix) const {
    std::string fileName;
    std::cout << "Enter output location data:\n";

    try {
        std::cout << "Fully qualified path and filename:\n";
        std::cin >> fileName;

        // Handle input errors and crashes gracefully
        if (!std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default value to /Users/Black-Scholes Option Data.xlsx";
            fileName = "/Users/Black-Scholes Option Data.xlsx";
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}