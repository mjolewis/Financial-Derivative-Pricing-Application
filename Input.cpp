/**********************************************************************************************************************
 * Function definitions Input.hpp
 * An Input class is used to get and set necessary option data from the user.
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#include "Input.hpp"

#include <boost/tuple/tuple_io.hpp>
#include <iostream>

/**
 * Initialize a new Input object
 * @throws OutOfMemoryException Indicates insufficient memory for this new Input object
 */
Input::Input() {}

/**
 * Initialize a new Input object with the specified option data
 * @param optionData_ A {@link boost::tuple} containing values to initialize core option data (e.g expiry,
 * volatility, risk-free rate, spot price, strike price, option type, European or American)
 * @throws OutOfMemoryException Indicates insufficient memory for this new Input object
 */
Input::Input(const OptionData &optionData_) : T(optionData_.get<0>()), sig(optionData_.get<1>()),
                                              r(optionData_.get<2>()), S(optionData_.get<3>()),
                                              K(optionData_.get<4>()), b(optionData_.get<5>()),
                                              optType(optionData_.get<6>()), optFlavor(optionData_.get<7>()) {}

/**
 * Initialize a new Input object with the specified option data
 * @param T_ Time to expiry
 * @param sig_ Volatility
 * @param r_ Risk-free interest rate
 * @param S_ Spot price of the underlying
 * @param K_ Strike price
 * @param b_ Cost of carry
 * @param optType_ A put or a call
 * @param optFlavor_ European or American option
 * @throws OutOfMemoryException Indicates insufficient memory for this new Input object
 */
Input::Input(double T_, double sig_, double r_, double S_, double K_, double b_, std::string &optType_,
             std::string &optFlavor_) :
        T(T_), sig(sig_), r(r_), S(S_), K(K_), b(b_), optType(optType_), optFlavor(optFlavor_) {}

/**
 * Initialize a new Input object using the member data of the source
 * @param source An Input object whose data members will be used to initialize this Input objects members
 * @throws OutOfMemoryException Indicates insufficient memory for this new Input object
 */
Input::Input(const Input &source) : T(source.T), sig(source.sig), r(source.r), S(source.S), K(source.K),
                                    b(source.b), optType(source.optType), optFlavor(source.optFlavor) {}

/**
 * Destory's this Input object
 */
Input::~Input() {}

/**
 * Create a deep copy of the source Input object
 * @param source An Input object which will be deeply copied
 * @return A reference to an Input object
 */
Input &Input::operator=(const Input &source) {
    // Avoid self assign
    if (this == &source) { return *this; }

    T = source.T;
    sig = source.sig;
    r = source.r;
    S = source.S;
    K = source.K;
    b = source.b;
    optType = source.optType;
    optFlavor = source.optFlavor;

    return *this;
}

const std::vector<double>& Input::getMeshData() {
    double a, b;
    int J;

    std::cout << "\nEnter the required mesh data:\n";

    // Get parameters
    try {
        std::cout << "Domain of integration min value: ";
        std::cin >> a;

        // Handle input errors and crashes gracefully
        if (a < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default value to 0\n";
            a = 0;

            // Add value to end of vector
            meshData.push_back(0);
        }

        std::cout << "Domain of integration max value: ";
        std::cin >> b;

        // Handle input errors and crashes gracefully
        if (b < 0 || b < a || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default value to 1\n";
            b = 1;

            // Add value to end of vector
            meshData.push_back(b);
        }

        std::cout << "Factor: ";
        std::cin >> J;

        // Handle input errors and crashes gracefully
        if (J < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default value to 100\n";
            J = 100;

            // Add value to end of vector
            meshData.push_back(J);
        }
    } catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }

    return meshData;
}

/**
 * Accessor that retrieves OptionData
 * @return A {@link boost::tuple<>} representing core option data (e.g. Expiry, Sig, r, S, K, b, optType, optFlavor)
 */
OptionData Input::getOptionData() const { return boost::make_tuple(T, sig, r, S, K, b, optType, optFlavor); }

/**
 * Get option data from the client and set member data
 * @return A {@link boost::tuple<>} representing an equity option
 */
OptionData Input::getOptionInput() {
    std::cout << "\nEnter the required option data:\n";

    // Get parameters
    try {
        std::cout << "Expiry: ";
        std::cin >> T;

        // Handle input errors and crashes gracefully
        if (T < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "\nIncorrect input. Setting default expiry to 3 months\n";
            T = 0.25;                            // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Volatility: ";
        std::cin >> sig;

        // Handle input errors and crashes gracefully
        if (sig < 0 || !std::cin) {
            // Sig can theoretically be positive infinity. Add boundary if desired

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "\nIncorrect input. Setting default volatility to 30%\n";
            sig = 0.3;                           // Pg. 36 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Risk-free interest rate: ";
        std::cin >> r;

        // Handle input errors and crashes gracefully
        if (r < 0 || !std::cin) {
            // Rate can theoretically be positive infinity. Add boundary if desired

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "\nIncorrect input. Setting default risk-free rate to 8%\n";
            r = 0.08;                            // Pg. 36 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Stock price: ";
        std::cin >> S;

        // Handle input errors and crashes gracefully
        if (S < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default stock price to $60\n";
            S = 60;                              // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Strike price: ";
        std::cin >> K;

        // Handle input errors and crashes gracefully
        if (K < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set a default value
            std::cout << "Incorrect input. Setting default stock price to $65\n";
            K = 65;                              // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Cost of carry: ";
        std::cin >> b;

        // Handle input errors and crashes gracefully
        if (b < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Incorrect input. Setting default beta to risk-free rate\n";
            b = r;                              // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
        }

        std::cout << "Put or Call: ";
        std::cin >> optType;
        if (optType == "call") { optType = "Call"; }
        if (optType == "put") { optType = "Put"; }

        // Handle input errors and crashes gracefully
        if (optType != "Put") {
            if (optType != "Call") {
                // Clear the error flag
                std::cin.clear();

                // Ignore input up to stream size or new line (whichever comes first)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Set a default value
                std::cout << "Incorrect input. Setting default to a Call option\n";
                optType = "Call";                // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
            }
        }

        std::cout << "European or American: ";
        std::cin >> optFlavor;
        if (optFlavor == "european") { optFlavor = "European"; }
        if (optFlavor == "american") { optFlavor = "American"; }

        // Handle input errors and crashes gracefully
        if (optFlavor != "European") {
            if (optFlavor != "American") {

                // Clear the error flag
                std::cin.clear();

                // Ignore input up to stream size or new line (whichever comes first)
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                // Set a default value
                std::cout << "Incorrect input. Setting default to a European option\n";
                optFlavor = "European";              // Pg. 37 of Intro to C++ for Financial Engineers by Dr. Duffy
            }
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return boost::make_tuple(T, sig, r, S, K, b, optType, optFlavor);
}

void Input::setOptionData(double T_, double sig_, double r_, double S_, double K_, double b_,
                          const std::string& optType_, const std::string& optFlavor_) {

    T = T_;
    sig = sig_;
    r = r_;
    S = S_;
    K = K_;
    b = b_;
    optType = optType_;
    optFlavor = optFlavor_;
}
