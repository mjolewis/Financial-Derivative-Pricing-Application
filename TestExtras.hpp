/**********************************************************************************************************************
 * Black-Scholes Option Pricer
 *
 * Test extra functionality. Can remove before publishing. Separated from Main to improve readability
 *
 * Created by Michael Lewis on 7/27/20.
 *********************************************************************************************************************/

#ifndef TESTEXTRAS_HPP
#define TESTEXTRAS_HPP

#include "Builder.hpp"
#include "Input.hpp"
#include "RNG.hpp"
#include "Option.hpp"
#include "Pricer.hpp"

typedef boost::tuple<double, double, double, double, double, double, std::string, std::string> OptionData;
class TestExtras {
public:
    TestExtras() {};
    virtual ~TestExtras() {};

    void RunTest() {

        // Test builder extras
        Builder<Input, RNG, Option, Pricer> Builder1;
        Builder<Input, RNG, Option, Pricer> Builder2;
        Builder<Input, RNG, Option, Pricer> Builder3(Builder1);
        Builder1 = Builder2;

        // Test Input extras
        OptionData optionData = boost::make_tuple(0.25, 0.30, 0.08, 60, 65, 0.30, "Call", "European");
        std::string optType = "Call";
        std::string optFlavor = "European";
        Input input1;
        Input input2;
        Input input3(input1);
        Input input4(optionData);
        Input input5(0.25, 0.30, 0.08, 60, 65, 0.30, optType, optFlavor);
        Input input6(input5);
        input6.setOptionData(0.25, 0.30, 0.08, 100, 65, 0.30, optType, optFlavor);
        input1 = input2;
        input6.getOptionData();

        // Test Instrument extras
        Instrument instrument1;
        Instrument instrument2;
        Instrument instrument3(instrument1);
        instrument1 = instrument2;

        // Test Option extras
        Option option1;
        Option option2;
        std::string uName = "GS";
        Option option3(0.25, 0.30, 0.08, 60, 65, 0.30, optType, optFlavor, uName);
        Option option4(option3);
        option3 = option4;
        double T_ = option3.expiry();
        double sig_ = option3.vol();
        double r_ = option3.riskFree();
        double S_ = option3.spot();
        double K_ = option3.strike();
        double b_ = option3.carry();
        const std::string& optType1 = option3.type();
        const std::string& optFlavor1 = option3.flavor();
        const std::string& uName1 = option3.underlying();

        // Test RNG
        RNG rng1;
        RNG rng2;
        RNG rng3(rng2);
        RNG rng4("Mersenne");
        rng1 = rng2;
        double cdf = rng1.CDF(0.5);
        double pdf = rng1.PDF(0.5);
        double mersenne = rng1.MersenneTwister();
        const std::string& name = rng4.getRNGName();

        // Test Pricer
        Pricer<Input, RNG, Option> pricer1;
        Pricer<Input, RNG, Option> pricer2;
        pricer1 = pricer2;
    }
};

#endif // TESTEXTRAS_HPP
