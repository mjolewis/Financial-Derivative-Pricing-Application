/**********************************************************************************************************************
 * Black-Scholes Option pricing application - Output class
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <vector>
#include <iostream>
#include <fstream>

class Output {

private:

    std::ofstream outFile;                       // Object for writing to a file

public:
    // Constructors and destructors
    Output();
    Output(const Output& source);
    virtual ~Output();

    // Operator overloading
    Output& operator=(const Output& source);

    // Core functionality
    void sendToFile(double value);
    void sendToFile(const std::vector<std::vector<double>>& matrix) const;

};


#endif // OUTPUT_HPP
