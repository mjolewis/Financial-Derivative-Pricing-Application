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

public:
    // Constructors and destructors
    Output();
    Output(const Output& source);
    virtual ~Output();

    // Operator overloading
    Output& operator=(const Output& source);

    // Core functionality
    void sendToFile(double value) const;
    void sendToFile(const std::vector<std::vector<double>>& matrix) const;

};


#endif // OUTPUT_HPP
