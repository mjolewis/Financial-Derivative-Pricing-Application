# Financial-Derivative-Pricing-Application

# Description
This application can be used by Financial Engineers to price financial derivatives. In particular, the application is capable of dealing with European and Perpetual American options but can be extended for additional option types.

To use the application, you should create a European or American option with the required option parameters (T (European only), sig, r, S, K, and b). Afterward, you can use various functions and methodologies (closed form or finite difference methods) to price the options and to determine their sensitivities (European only).

Importantly, you can send the option data directly to the console or to a CSV file on your current path. The latter approach is recommended. The only requirement is to price the option using the function that is pre-built to send data to the CSV file.

# Libraries
The application uses STL for Containers and the Boost library to generate the Guassian probability density and cumulative normal distribution functions. As a result, you must download and include the Boost libraries to compile the application on your machine. 

Note that there are multiple ways to install Boost: 
1. SourceForce: https://sourceforge.net/projects/boost/files/boost-binaries/
2. Homebrew: https://brew.sh/ and run brew install boost 
3. MacPorts: https://www.macports.org/ and run sudo port install boost 

# System Analysis
This application was decomposed into smaller subsystems, with each subsystem having a well-defined responsibility. The class descriptions provided below highlight these subsystems, along with their indications and parameters for implementation.

***AmericanOption***\
The AmericanOption class relies on Template Metroprogamming and Policy-Based Design. Importantly, this is a host class for the various policies (Mesher, Matrix, Output) mentioned below. Please see System Design for additional detail. 

American options can be exercised at any time prior to expiry and generally do not have an exact solution. However, Perpetual American options are the exception because the expiry time tends to infinity. Thus, this application appropriately implements the formulae to provide an exact solution for Perpetual American options. 

Finally, the pricing functions always return a matrix where the first element of each row is the Call price and the second element of each row is the Put price. This approach ensures that all relevant pricing information is received and makes the system more usable from an analytics perspective.

***EuropeanOption***\
The EuropeanOption class relies on Template Metroprogamming and Policy-Based Design. Importantly, this is a host class for the various policies (Mesher, Matrix, RNG, Output) mentioned below. Please see System Design for additional detail. 

A EuropeanOption is a financial derivative and has the following core member data: T, sig, r, S, K, and b. These options can only be exercised at expiration and, as a result, have prices and sensitivities calculated by the generalized Black-Scholes formulae. 

We also know the option sensitivities are the partial derivatives of the Black-Scholes option pricing formula with respect to one of its parameters and, therefore, can rely on closed form solutions for the Greeks in most cases. However, a closed form solution is not guaranteed or can be difficult to find. For those scenarios, I implemented the divided differences method to find a numerical solution.

There is also a relationship between Call and Put prices of a European option. This relationship is defined by the Put-Call parity formula where the Put and Call have the same strike, expiration, and underlying. This relationship can also be tested for a corresponding Put (or Call) price, which helps us exploit arbitrage opportunities if the relationship is not satisfied.

Finally, the pricing functions always return a matrix where the first element of each row is the Call price and the second element of each row is the Put price. This approach ensures that all relevant pricing information is received and makes the system more usable from an analytics perspective.


***Mesher***\
A Mesher class is a policy used by the financial derivative host classes. It is responsible for creating a one-dimensional domain of mesh points. The mesh points are bounded by [start, stop] and separated by a step size. The Mesher creates an array of a monotonically increasing range for any of the option datum. This mesh array is then fed into the Matrix.

***Matrix***\
A Matrix class is a policy used by the financial derivative host classes. It is responsible for creating a container of option parameters. Each row in the matrix will be identical except for the option parameter that has been monotonically increased by the Mesher.

The container is then consumed by the financial derivative host classes where a Call and Put price is determined for each row of option data. This mechanism allows for the efficient pricing of a wide range of option data that can then be analyzed to show how a change in the single varying parameter impacts Call and Put prices (as well as their Greeks in the case of EuropeanOptions).

***RNG***\
An RNG class is a policy used by the financial derivative host classes. The RNG is responsible for generating the cumulative normal distribution function used to price EuropeanOptions. This class relies on the Boost library.

Additionally, this class provides the normal (Gaussian) probability density function as well as the ability to generate a standard normal distribution using the Mersenne Twister random number generator. 

***Output***\
An Output class is a policy used by the financial derivative host classes. The Output is responsible for receiving data matrices from the financial derivative host classes. Upon receiving these matrices, the Output's sole job is to create a CSV file and parse the matrices into rows and columns.

The CSV file is titled either European_Option_Data or American_Option_Data and is appended with the current date and time to create unique file names across multiple simulations.

Sending data to the CSV file is the recommended approach because it allows for easier analysis, charting, and data sharing. However, the output data can be written directly to the console as well.

See the sample-output folder for an example. This file includes the option Call and Put prices as well as associated option sensitivities (Greeks).

# System Design
The application implements Template Metroprogamming and Policy-Based Design. These design choices provide several benefits.

For example, host classes derive from each of its policies but do not violate the IS-A relationship because Policy-Based Design inverts the relationship between base class and derived class. An alternative design choice could have been Composition or Aggregation. However, both of these designs would have violated core OOP principles:
     
   1.	Composition would have required creating false HAS-A relationships
   2.	Aggregation would have created objects that survive past the lifetime of a financial derivative even though there is no use for them once the financial derivative has gone out of scope

The policies also encapsulate an orthogonal behavior of the host class, which modularizes the application. Therefore, the application can easily be extended by creating additional policies that subsequently get supplied to the host classes.

As stated, Policy-Based Design relies on Template Metaprogramming. This means the system is parametric polymorphic, which avoids the cost of virtual lookup tables associated with subtype polymorphism.

UML Diagram:
![UML (3)](https://user-images.githubusercontent.com/12025538/91356153-34ddae80-e7bd-11ea-83b8-1404852f3316.png)

