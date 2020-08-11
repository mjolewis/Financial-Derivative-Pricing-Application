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
Input::Input() : T(0.25), sig(0.3), r(0.08), S(60), K(65), b(0.08), optType("Call"),
                  optFlavor("European"), uName("N/A") {}

/**
 * Initialize a new Input object using the member data of the source
 * @param source An Input object whose data members will be used to initialize this Input objects members
 * @throws OutOfMemoryException Indicates insufficient memory for this new Input object
 */
Input::Input(const Input &source) : T(source.T), sig(source.sig), r(source.r), S(source.S), K(source.K), b(source.b),
                                    optType(source.optType), optFlavor(source.optFlavor), uName(source.uName),
                                    option(source.option) {}

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
    uName = source.uName;
    option.setOptionData(source.T, source.sig, source.r, source.S, source.K,
            source.b, source.optType, source.optFlavor, source.uName);

    for (int i = 0; i < meshData.size(); i++) {
        meshData[i] = source.meshData[i];
    }

    return *this;
}

/**
 * Accessor that retrieves the Option
 * @return A new option with Expiry, Sig, r, S, K, b, uName, optType, optFlavor
 */
const Option& Input::getOptionData() const {return option;}

const std::vector<double>& Input::setMeshData() {
    double start, stop;
    int J;

    std::cout << "\nEnter the required mesh data:\n";

    // Get parameters
    try {
        std::cout << "Domain of integration min value: ";
        std::cin >> start;

        // Handle input errors and crashes gracefully
        if (start < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set start default value
            std::cout << "Incorrect input. Setting default value to 0\n";
            start = 0;

            // Add value to end of vector
            meshData.push_back(0);
        }

        std::cout << "Domain of integration max value: ";
        std::cin >> stop;

        // Handle input errors and crashes gracefully
        if (stop < 0 || stop < start || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set start default value
            std::cout << "Incorrect input. Setting default value to 1\n";
            stop = 1;

            // Add value to end of vector
            meshData.push_back(stop);
        }

        std::cout << "Factor: ";
        std::cin >> J;

        // Handle input errors and crashes gracefully
        if (J < 0 || !std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            // Set start default value
            std::cout << "Incorrect input. Setting default value to 100\n";
            J = 100;

            // Add value to end of vector
            meshData.push_back(J);
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return meshData;
}

/**
 * Provide a console interface to dynamically get option data
 * @return An Option whose member data is either user defined or the default values if incorrect input is provided
 */
const Option& Input::setOptionData() {
    std::cout << "\nEnter the required option data:\n";

    // Get core option data
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

        std::cout << "Name of underlying: ";
        std::cin >> uName;

        // Handle input errors and crashes gracefully
        if (!std::cin) {

            // Clear the error flag
            std::cin.clear();

            // Ignore input up to stream size or new line (whichever comes first)
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Incorrect input. Setting default underlying name to N/A";
            uName = "N/A";
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

    option.setOptionData(T, sig, r, S, K, b, optType, optFlavor, uName);
    return option;
}
