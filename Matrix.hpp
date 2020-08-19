/**********************************************************************************************************************
 * Utility class to generate matrices
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>

#include "Option.hpp"

class Matrix {
private:
public:
    Matrix();
    Matrix(const Matrix& source);
    virtual ~Matrix();

    // Operator overloading
    Matrix& operator=(const Matrix& source);

    // Generate matrices
    std::vector<std::vector<double>>
    americanMatrix(const std::vector<double>& mesh, const Option& option, const std::string& property) const;

    std::vector<std::vector<double>>
    europeanMatrix(const std::vector<double>& mesh, const Option& option, const std::string& property) const;

    std::vector<std::vector<double>>
    futuresMatrix(const std::vector<double>& mesh, const Option& option, const std::string& property) const;

};


#endif // MATRIX_HPP
