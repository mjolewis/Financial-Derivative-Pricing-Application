# Black-Scholes-Option-Pricer

# Description
The Black-Scholes Pricer can be used by Financial Engineers to calculate an exact solution for European equity options and perpetual American equity options. The Pricer requires a set of option configuration data that can be specified by the user or provided by the system itself. When the data is specified by the system, it relies on default values as determined by Dr. Duffy in C++ for Financial Engineers. Note that this configuration data includes Expiry, Volatility, Risk-Free Rate, Spot price, Strike price, and Beta.

The application attempts to implement the single responsiblity principle and, as a result, has multiple classes that are designed to handle their individual subproblems well. For example, the Builder acts as the system controller responsible for separating the construction of complex objects from the object representation while simultaneously managing the data flow and assembly process. The Input gets option data from the user (or sets default data) and the Builder subsequently passes that data to the Pricer. The Greeks calculates option sensitivies, which are the partial derivatives of the Black-Scholes option pricing formula with respect to one of its parameters. Note that any given Greek is a measure of the sensitivity of the option price with respect to a small change in the options parameter. The Pricer itself implements the Black-Scholes one factor option pricing formula to determine the exact solutions to either a European equity option or a perpetual American equity option. Finally, the simulation results are sent to the Output and presented to the user via the console.

# Libraries
The system uses STL for Containers, Algorithms, and Iterators. Additionally, the system uses the Boost library for the boost::tuple data container in favor of stl::tuple simply out of a preference for how the get<>() function is treated as a member function in Boost versus being a free function in STL. Finally, the Boost library is used to generate the Guassian probability density function and the cumulative normal distribution function. As a result, you must download and include the Boost libraries to compile the application on your machine. 

Note that there are multiple ways to get Boost. A few common ways to install Boost are to get the Boost Wizard from SourceForge or, if on a Mac, to use MacPorts or Homebrew. 

# System Analysis
The system was decomposed into smaller subsystems with each subsystem having a well-defined responsibility. The concept mapping below highlights the subsystems used and their associated relationship and data flow. 

![Data Flow Diagram (2)](https://user-images.githubusercontent.com/12025538/88865065-c82ebe80-d1d4-11ea-9765-e314b66ada67.png)

# System Design

# Output
