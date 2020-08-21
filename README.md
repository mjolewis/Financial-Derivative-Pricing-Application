# Black-Scholes-Option-Pricer

# Description
The Black-Scholes pricing application can be used by Financial Engineers to price financial derivates (options in particular) and to calculate the associated option sensitivies (Greeks).

The simulation showcases plain (European) and Perpetual American equity options and, as a result, relies on the generalized Black-Scholes formula to calculate an exact solution for the option prices. We also know the option sensitivities are the partial derivatives of the Black-Scholes option pricing formula with respect to one of its parameters and, therefore, can rely on closed form solutions for the Greeks in most cases. However, a closed form solution isn't guaranteed or can be difficult to find. For those scenarios, I implemented the divided differences method to find a numerical solution.

To use the system, you can either create an option with the required option parameters or pass those values directely to an overloaded pricing function. When creating an option, you must specify the Expiry, Volatility, Risk-Free Rate, Spot price, Strike price, and Beta.

# Libraries
The system uses STL for Containers and Iterators. Additionally, the system uses the Boost library to generate the Guassian probability density function and the cumulative normal distribution function. As a result, you must download and include the Boost libraries to compile the application on your machine. 

Note that there are multiple ways to get Boost. 
1. SourceForce: https://sourceforge.net/projects/boost/files/boost-binaries/
2. Homebrew: https://brew.sh/ and run brew install boost 
3. MacPorts: https://www.macports.org/ and run sudo port install boost 

# System Analysis
The system was decomposed into smaller subsystems with each subsystem having a well-defined responsibility. The concept mapping below highlights the subsystems used and their associated relationship and data flow. At a macro level, the Pricer acts as the kernal and delegates responsibility whenever it's logical to do so. 

*Instrument*
The base class for all Options. This class is currently plain, but could provide additional benefits in the future as more instruments are added to the system or if we wanted to enforce certain contraints on any derived class.

*Option*

*Mesher*

*Matrix*

*RNG*

*Pricer*
The Pricer relies on Template Metroprogamming techniques. In particular, the Pricer uses Template Inheritance to avoid creating false composition relationships because a Pricer does not have a HAS-A relationship with an RNG, Mesher, Matrix, or Output class. Template Inheritance also makes the system more efficient because it avoids passing potentially large objects around through aggregation techniques. Instead, each Pricer calls the default constructor for its inherited template parameters and those objects exist until the Pricer goes out of scope. Additionally, templates are parametric polymorphic, which is significantly faster than subtype polymorphism. 

*Output*
The sole job of Output is to send option data (prices and Greeks) directly to a CSV file. This approach provides obvious benefits such as allowing a user to perform additional analysis on the option data and to also more easily share that data wherever appropriate.

# System Design
![UML](https://user-images.githubusercontent.com/12025538/90795325-e7080880-e2db-11ea-98c2-d570c67e2c91.png)

# Output
The output data can be written directly to the console or to a CSV file on the current path. The CSV file is titled OptionData and is appended with the current date and time to create unique file names across multiple simulations.

Sending data to the CSV file is the recommended approach because it allows you to more easily analyze, chart, and share data. See the sample-output folder for an example. This file includes the option call and put prices as well as associated option sensitivities (Greeks).
