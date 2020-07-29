/**********************************************************************************************************************
 * Function declarations for Input.hpp
 * An Input class is used to get and set necessary option data from the user.
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/tuple/tuple_io.hpp>

// Alias for required option data (e.g. expiry, volatility, risk-free rate, spot
typedef  boost::tuple<double, double, double, double, double> OptionData;
namespace MJL {
    namespace Input {
        class Input {
        private:
            // Required option data
            double T;                            // Expiry time/maturity. E.g. T = 1 means one year
            double sig;                          // Volatility
            double r;                            // Risk-free interest rate
            double S;                            // Spot price
            double K;                            // Strike price
            OptionData optionData;               // Holds the option data
        public:
            // Constructors and destructor
            Input();
            Input(const OptionData& optionData_);
            Input(double& T_, double& sig_, double& r_, double& S_, double& K_);
            Input(const Input& source);
            virtual ~Input();

            // Operator overloading
            Input& operator=(const Input& source);

            // Getters
            const OptionData& getOptionData() const;

            // Setters
            const OptionData& setOptionData();   // Get input from the user and initialize option data
        };
    }
}


#endif //INPUT_HPP
