# Black-Scholes-Option-Pricer

# Description
The Black-Scholes simulation application can be used by Financial Engineers to price financial derivates (options in particular) and to calculate the associated option sensitivies (Greeks). 

The simulation showcases plain (European) and Perpetual American equity options and, as a result, relies on the generalized Black-Scholes formula to calculate an exact solution for the option prices. We also know the option sensitivities are the partial derivatives of the Black-Scholes option pricing formula with respect to one of its parameters and, therefore, can rely on closed form solutions for the Greeks in most cases. However, a closed form solution isn't guaranteed or can be difficult to find. For those scenarios, I implemented the divided differences method to find a numerical solution.

The Pricer requires a set of option configuration data that can be specified by the user or provided by the system itself. When the data is specified by the system, it relies on default values as determined by Dr. Duffy in C++ for Financial Engineers. Note that this configuration data includes Expiry, Volatility, Risk-Free Rate, Spot price, Strike price, and Beta.

Finally, the system relies on the single responsiblity principle and, as a result, has multiple classes that are designed to handle their individual subproblems well. For example, the Builder acts as the system controller responsible for separating the construction of complex objects from the object representation while simultaneously managing the data flow and assembly process. The Input gets option data from the user (or sets default data) and the Builder subsequently passes that data to the Pricer, which is where the Black-Scholes one factor option pricing formulae are implemented. Finally, the Output class can send the results to a file specified by the user. Please see the System Analysis and System Design sections for a more detailed overview.

Please note that the user can avoid the console input component and gain direct access the the necessary classes. This approach allows us to run large numbers of automated scenarios (e.g. montonically increasing option parameters) instead of being required to manually enter new parameters for each scenario.

# Libraries
The system uses STL for Containers and Iterators. Additionally, the system uses the Boost library to generate the Guassian probability density function and the cumulative normal distribution function. As a result, you must download and include the Boost libraries to compile the application on your machine. 

Note that there are multiple ways to get Boost. 
1. SourceForce: https://sourceforge.net/projects/boost/files/boost-binaries/
2. Homebrew: https://brew.sh/ and run brew install boost 
3. MacPorts: https://www.macports.org/ and run sudo port install boost 

# System Analysis
The system was decomposed into smaller subsystems with each subsystem having a well-defined responsibility. The concept mapping below highlights the subsystems used and their associated relationship and data flow. At a macro level, the Pricer acts as the kernal and delegates responsibility whenever it's logical to do so. 

Console Interface:
![Data Flow Diagram](https://user-images.githubusercontent.com/12025538/90526012-e0dc2580-e13d-11ea-925a-bf68375e10a6.png)

Direct Access
![Data Flow Diagram Automated (1)](https://user-images.githubusercontent.com/12025538/90527117-2e0cc700-e13f-11ea-87e5-0ae9e9f88618.png)

# System Design

# Output
The output data is sent directly to Microsoft Excel by default and, therefore, you must have Excel installed on your system. To do this, you need to update the mso.dll, vbe6ext.olb, and EXCEL.exe file paths to point to wherever these files are installed on your system. 

The Output folder included in this project provides sample output data that you can use as a reference.
