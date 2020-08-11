/**********************************************************************************************************************
 * Output class for the Black-Scholes Option pricing application. Sends Option output data to a file specified by the
 * user
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

class Output {

private:
public:
    // Constructors and destructors
    Output();
    Output(const Output& source);
    virtual ~Output();

    // Operator overloading
    Output& operator=(const Output& source);

};


#endif // OUTPUT_HPP
