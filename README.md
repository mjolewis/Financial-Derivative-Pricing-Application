# Financial-Derivative-Pricing-Application

# Description
The option pricing application can be used by Financial Engineers to price financial derivatives. In particular, the pricing application provides solutions for European and Perpetual American equity options and their associated option sensitivities (Greeks).

In general, only European options and Perpetual American options have closed form solutions and this application implements the appropriate formulae for each. We also know the option sensitivities are the partial derivatives of the Black-Scholes option pricing formula with respect to one of its parameters and, therefore, can rely on closed form solutions for the Greeks in most cases. However, a closed form solution isn't guaranteed or can be difficult to find. For those scenarios, I implemented the divided differences method to find a numerical solution.

To use the system, you can either create an option with the required option parameters or pass those values directly to an overloaded pricing function. In either case, you must specify the Expiry, Volatility, Risk-Free Rate, Spot price, Strike price, and Beta.

# Libraries
The system uses STL for Containers and Iterators. Additionally, the system uses the Boost library to generate the Guassian probability density function and the cumulative normal distribution function. As a result, you must download and include the Boost libraries to compile the application on your machine. 

Note that there are multiple ways to get Boost. 
1. SourceForce: https://sourceforge.net/projects/boost/files/boost-binaries/
2. Homebrew: https://brew.sh/ and run brew install boost 
3. MacPorts: https://www.macports.org/ and run sudo port install boost 

# System Analysis
This option pricing application was decomposed into smaller subsystems, with each subsystem having a well-defined responsibility. The class descriptions provided below highlight these subsystems, along with their indications and parameters for implementation. At a macro level, the Pricer acts as the kernel and delegates responsibility whenever it is logical to do so.

***Instrument***\
The base class for all financial instruments. This class is currently plain but could provide additional benefits in the future as more instruments are added to the system or, should any constraints on any derived class be desirable.

***Option***\
A financial derivative has the following core member data: T, sig, r, S, K, and b. An Option also provides accessors and mutators for each of the core member datum.

There is also a relationship between Call and Put prices of a European option. This relationship is defined by the Put-Call parity formula where the Put and Call have the same strike, expiration, and underlying. Generally, this formula applies to European options because they can only be exercised on expiration. However, in theory, the relationship still holds for American options held to expiration. Therefore, as a user, you must ensure that this principle is not violated when using the put-call parity function for an American option.

Finally, the Put-Call relationship can be used as a mechanism to calculate the Call (or Put) price for a corresponding Put (or Call) price or as a mechanism to check if a given set of Put and Call prices satisfy parity. If not, then an arbitrage opportunity exists.

***Mesher***\
Creates a one-dimensional domain of mesh points. The mesh points are bounded by [start, stop] and separated by a step size. The Mesher creates an array of a monotonically increasing range for any of the Option datum. This mesh array is then fed into the Matrix.

***Matrix***\
A Matrix generates a container of option parameters. Each row in the matrix will be identical except for the Option parameter that has been monotonically increased by the Mesher.

The matrix is then fed into the Pricer so one can efficiently price a wide range of options and evaluate how a change in the single varying parameter impacts Call and Put prices as well as their associated Greeks.

***RNG***\
The RNG uses the Boost library to generate the normal (Gaussian) probability density function, as well as the cumulative normal distribution function, which are both used to price European options.

A standard normal distribution can also be generated using the Mersenne Twister random number generator from the Boost Random library. Note that a normal distribution with a mean of 0 and standard deviation of 1 is known as the Standard Normal Distribution.

***Pricer***\
The Pricer relies on Template Metroprogamming techniques. In particular, the Pricer uses Template Inheritance to avoid creating false composition relationships because a Pricer does not have a HAS-A relationship with an RNG, Mesher, Matrix, or Output. Template Inheritance also makes the system more efficient because it avoids passing potentially large objects around, which would be required if the system implemented aggregation techniques. Instead, each Pricer calls the default constructor for its inherited template parameters and those objects exist until the Pricer goes out of scope. Additionally, templates are parametric polymorphic, which is significantly more efficient than subtype polymorphism.

A Pricer has the obvious job of pricing a financial derivative. As such, it includes functions to appropriately price European and Perpetual American equity options.

European options are priced using the generalized Black-Scholes formulae because they can only be exercised at the expiry date and an exact solution is known.

Alternatively, American options can be exercised at any time prior to expiry and generally do not have an exact solution. However, Perpetual American options are the exception because the expiry time tends to infinity. Thus, this application appropriately implements the formulae to provide an exact solution for Perpetual American options. 

Additionally, the Pricer calculates option sensitivities (Delta and Gamma) using either the closed-form or divided difference formulae.

Finally, the pricing functions always return a matrix where the first element of each row is the Call price and the second element of each row is the Put price. This approach ensures that all relevant pricing information is received and makes the system more usable from an analytics perspective.

***Output***\
The Pricer sends multiple matrices of option data directly to the Output. This includes matrices for Mesh Points, Call and Put prices, Call and Put Deltas, and Gammas. Upon receiving these matrices, the Output's sole job is to create a CSV file and parse the matrices into rows and columns.

The CSV file is titled OptionData and is appended with the current date and time to create unique file names across multiple simulations.

Sending data to the CSV file is the recommended approach because it allows for easier analysis, charting, and data sharing. However, the output data can be written directly to the console as well.

See the sample-output folder for an example. This file includes the option Call and Put prices as well as associated option sensitivities (Greeks).

# System Design
![UML (1)](https://user-images.githubusercontent.com/12025538/90927449-2198a080-e3c3-11ea-9522-158d46427b8b.png)

