/**********************************************************************************************************************
 * Function declarations for Input.hpp
 * An Input class is used to get and set necessary option data from the user.
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef INPUT_HPP
#define INPUT_HPP

#include <boost/tuple/tuple_io.hpp>
#include <vector>
#include <string>

// Stores option data (e.g. expiry, volatility, risk-free rate, spot, option type
typedef boost::tuple<double, double, double, double, double, std::string> OptionData;
namespace MJL {
    namespace Input {
        class Input {
        private:
            // Required option data
            double T = 0.25;                           // Expiry time/maturity. E.g. T = 1 means one year
            double sig = 0.3;                          // Volatility
            double r = 0.08;                           // Risk-free interest rate
            double S = 60;                             // Spot price
            double K = 65;                             // Strike price
            std::string optType = "Call""";            // Call or Put
        public:
            // Constructors and destructor
            Input();
            explicit Input(const OptionData& optionData_);
            Input(double T_, double sig_, double r_, double S_, double K_, std::string& optType_);
            Input(const Input& source);
            virtual ~Input();

            // Operator overloading
            Input& operator=(const Input& source);

            // Getters
            OptionData getOptionData() const;

            // Setters
            OptionData setOptionData();
        };
    }
}

#endif //INPUT_HPP
