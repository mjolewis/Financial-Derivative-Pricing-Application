# Black-Scholes-Option-Pricer

# Description
The Black-Scholes Pricer can be used by Financial Engineers to calculate an exact solution for European equity options and perpetual American equity options. The pricer requires the user to provide the option parameters (e.g. Expiry, Volatility, Risk-Free Rate, Spot price of the underlying); otherwise, the application will provide default values as determined by Dr. Duffy in C++ for Financial Engineers.

The application attempts to implement the single responsiblity principle and, as a result, has multiple classes that feed data into the Pricer. The Input class gets option data from the user and subsequently provides that data to the Pricer. Additionally, the RNG class (random number generator) generates Gaussain random variates for the Pricer. Finally, the Pricer determines the exact solutions for the Call and Put prices and provides that data to the Output class which displays option data in the users console.

# Libraries
The system uses STL for Containers, Algorithms, and Iterators. Additionally, the system uses the Boost library for the boost::tuple data container in favor of stl::tuple simply out of preference for how Boost treats the get<>() function as a member function versus a being a free function in stl::boost. Finally, the Boost library is used to generate the Guassian probability density functions and the cumulative normal distribution function. As a result, you must download and include the Boost libraries to compile the application on your machine.

# System Analysis
The system was decomposed into smaller subsystems with each subsystem having a well-defined responsibility. The concept mapping below highlights the subsystems used and their associated relationship and data flow. 

![Data Flow Diagram](https://user-images.githubusercontent.com/12025538/88860982-f5766f00-d1ca-11ea-8aaf-544f3d81173d.jpg)

# System Design

# Output
