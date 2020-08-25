/**********************************************************************************************************************
 * Utility class to generate matrices
 *
 * Created by Michael Lewis on 8/9/20.
 *********************************************************************************************************************/

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <string>

class Matrix {
private:
public:
    Matrix();
    Matrix(const Matrix& source);
    virtual ~Matrix();

    // Operator overloading
    Matrix& operator=(const Matrix& source);

    // Generate matrices
    static std::vector<std::vector<double>>
    matrix(const std::vector<double>& mesh, const std::string &property, double sig, double r, double S,
           double K, double b);

    static std::vector<std::vector<double>>
    matrix(const std::vector<double>& mesh, const std::string &property, double T, double sig, double r,
           double S, double K, double b);

    static std::vector<std::vector<double>>
    futuresMatrix(const std::vector<double>& mesh, const std::string &property, double T, double sig, double r,
                  double S, double K, double b);

};


#endif // MATRIX_HPP
