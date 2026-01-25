# Notes continued from README starting at [Chapter 7][0] 

## 7 - Block, Scope Linkage

### Compound Statements AKA blocks
Blocks are _zero or more statements that are treated by the compiler as if it were a single statement_ 
denoted by `{}`

Standard states 256 levels of nesting supported...

Functions cannot be nested, but blocks can be nested.

### User-Defined Namespaces and Scope Resolution Operator

`namespace` - a key word for segregating a namespace without classes!
```c++
namespace NameSpaceIdentifier
{
// content here!
}
```

If we have the same function in two different `.cpp` files and we try to declare the function with a forward declaration
in another - it will fail as it will have two definitions. 

If we __then__ enclose each in a namespace like the above, but still use the same forward declaration, we would get _another_
error. This is becomes the compiler was satisfied with the forward declaration, but the linker could not find 
the definition in the __global__ namespace. 

User defined namespaces restrict the scope of their contents.

__Methods for expressing to compiler which function__
1. `using` statements
2. `::` the scope resolution operator

Multiple name spaces are allowed:

circle.h
```c++
#ifndef CIRCLE_H
#define CIRCLE_H

namespace BasicMath
{
    constexpr double pi{ 3.14 };
}

#endif
```
growth.h
```c++
#ifndef GROWTH_H
#define GROWTH_H

namespace BasicMath
{
    // the constant e is also part of namespace BasicMath
    constexpr double e{ 2.7 };
}

#endif
```
main.cpp
```c++
#include "circle.h" // for BasicMath::pi
#include "growth.h" // for BasicMath::e

#include <iostream>

int main()
{
    std::cout << BasicMath::pi << '\n';
    std::cout << BasicMath::e << '\n';

    return 0;
}
```

#### 7 - localvariable quiz

1. Write a program that asks the user to enter two integers, one named smaller, the other named larger. 
If the user enters a smaller value for the second integer, use a block and a temporary variable to swap the smaller and 
larger values. Then print the values of the smaller and larger variables. Add comments to your code indicating 
where each variable dies. 
Note: When you print the values, smaller should hold the smaller input and larger the larger input, 
no matter which order they were entered in.
```c++
#include <iostream>

int getInteger(bool isLarger){
    
    std::string formatter{isLarger ? " a larger" : " an "};
    
    int x{};
    std::cout << "Enter" << formatter << "integer: ";
    std::cin >> x;
    
    return x;
}

void outputCommentary(int larger, int smaller){
    
    /* CHECK OUT std::swap to change the values of variables to eahc other! In the <utility> header!
    *   int temp{ larger };
        larger = smaller;
        smaller = temp;
        
        // is the same as
        std::swap(larger, smaller);
    * */
    if (larger < smaller){
        std::cout << "Swapping the values\n";
        int x{larger}; // x ends it duration at the end of the if block!
        larger = smaller;
        smaller = x;
        }
    std::cout << "The smaller value is " << smaller << '\n';
    std::cout << "The larger value is " << larger << '\n';
}

int main(){
    
    int larger{getInteger(true)};
    int smaller{getInteger(false)};
    
    outputCommentary(larger, smaller);

} 
```
### Linkage
__Linkage__ is a property that determines if other declarations of the same name rever to the same object or not.
Local variables have no linkage.

* Global variables and function identifiers have either `internal linkage` or `external linkage`

__Internal Linkage__
- it can be seen and used within a single _translation unit_ but not accessible in another translation unit.
- This means two source files with identical identifiers with internal linkage are treated as __independent__ and does not break
the One Declaration Rule (ODR).
- Variables with this specification are called __internal variables__.
- `const` and `constexpr` global variables have internal linkage by default.
- To give a global non-const variable internal linkage (limiting its accessibility) you use `static`
`static int g{};`.
- `static` is a `storage class specifier` - this sets the name's linkage AND its storage duration

* Unnamed namespaces give internal linkage to a wider range of identifiers. `static` for specificying internal linkage is fall
ing out of favour.
```c++
// Internal global variables definitions:
static int g_x;          // defines non-initialized internal global variable (zero initialized by default)
static int g_x{ 1 };     // defines initialized internal global variable

const int g_y { 2 };     // defines initialized internal global const variable
constexpr int g_y { 3 }; // defines initialized internal global constexpr variable

// Internal function definitions:
static int foo() {};     // defines internal function
```
__External Linkage__
External linkages extend use of the identifier beyond the source file to other files.
Forward declaration tells teh compiler of the existence of another function and the linker actually connects the definition
to the declaration.

- `const` and `constexpr` can be specified with external linkage using the `extern` specifier.
```c++
 // Global variable forward declarations (extern w/ no initializer):
extern int g_y;                 // forward declaration for non-constant global variable
extern const int g_y;           // forward declaration for const global variable
extern constexpr int g_y;       // not allowed: constexpr variables can't be forward declared

// External global variable definitions (no extern)
int g_x;                        // defines non-initialized external global variable (zero initialized by default)
int g_x { 1 };                  // defines initialized external global variable

// External const global variable definitions (extern w/ initializer)
extern const int g_x { 2 };     // defines initialized const external global variable
extern constexpr int g_x { 3 }; // defines initialized constexpr external global variable
```
### Inline functions and variables

From [here][1]: "When a call to min() is encountered, the CPU must store the address of the current instruction it is 
executing (so it knows where to return to later) along with the values of various CPU registers (so they can be restored 
upon returning). Then parameters x and y must be instantiated and then initialized. Then the execution path has to jump 
to the code in the min() function. When the function ends, the program has to jump back to the location of the function call, 
and the return value has to be copied so it can be output. This has to be done for each function call.
All the extra work that must happen to set up, facilitate, and/or cleanup after some task (in this case, making a 
function call) is called overhead.
For functions that are large and/or perform complex tasks, the overhead of the function call is typically
insignificant compared to the amount of time the function takes to run. However, for small functions 
(such as min() above), the overhead costs can be larger than the time needed to actually execute the function’s code! 
In cases where a small function is called often, using a function can result in a significant performance penalty over 
writing the same code in-place."

```c++

#include <iostream>

int min(int x, int y)
{
    return (x < y) ? x : y;
}

int main()
{
    // costly
    std::cout << min(5, 6) << '\n';
    std::cout << min(3, 2) << '\n';
    // less costly - and no min() storage!
    std::cout << ((5 < 6) ? 5 : 6) << << '\n';
    // because the literals are used the code could be optimised by the compiler to already output 5
    std::cout << ((3 < 2) ? 3 : 2) << << '\n';
    return 0;
}
```

### Static local variables

The static value is incremented with the previous value as the current value each time.

Static local variables that have no initializer or a non-constexpr initializer are zero-initialized at program start. 
Static local variables with a non-constexpr initializer are reinitialized the first time the variable definition is 
encountered. The definition is skipped on subsequent calls, so no futher reinitialization happens. Because they have 
static duration, static local variables that are not explicitly initialized will be zero-initialized by default.
```c++
#include <iostream>
void incrementAndPrint()
{
    static int s_value{ 1 }; // static duration via static keyword.  This initializer is only executed once.
     int s_value{ 1 }; // this would print 2 2 2 - not 2 3 4
    ++s_value;
    std::cout << s_value << '\n';
} // s_value is not destroyed here, but becomes inaccessible because it goes out of scope
int main()
{
    incrementAndPrint();
    incrementAndPrint();
    incrementAndPrint();
    return 0;
}
```
#### Common use ID Generation
ID generation gives a starting index and an incremental each time, very useful!
```c++
int generateID()
{
    static int s_itemID{ 0 };
    return s_itemID++; // makes copy of s_itemID, increments the real s_itemID, then returns the value in the copy
}
```
Static local constant variables are also useful as they are only iniitalized once - like a call to a database.
Rather than repeating the call, the one static call doesn't require re-initialisation eahc time.

Question:
What effect does using keyword static have on a global variable? What effect does it have on a local variable?

Textbook Answer:
When applied to a global variable, the static keyword defines the global variable as having internal linkage, 
meaning the variable cannot be exported to other files.
When applied to a local variable, the static keyword defines the local variable as having static duration, 
meaning the variable will only be created once, and will not be destroyed until the end of the program.

[Summary of Chapter 7][2]

### Unnamed and Inline Namespaces
```c++
#include <iostream>

namespace // unnamed namespace
{
    void doSomething() // can only be accessed in this file
    {
        std::cout << "v1\n";
    }
}
int main()
{
    doSomething(); // we can call doSomething() without a namespace prefix

    return 0;
}
```
This is useful as everything within the namespace has internal linkage and is only accessible within the file's scope.

## 9 Control Flow

Favour `constexpr` conditionals if the input is a `constexpr`

```c++
#include<iostream>

int main(){

    constexpr double gravity{ 9.8 };
    
    if constexpr (gravity == 9.8)
        std::cout << "Gravity is normal.\n";
    else
        std::cout << "Gravity is not normal.\n";
        
    // with if constexpr for the conditional the compiler can evaluate the conditional using the constexpr input
    // the entire if will compile to   
    std::cout << "Gravity is normal.\n";
}

```
#### Switch statements

The condition in a switch statement must evaluate to an integral time.
Floats, strings and non-integral types (other than enums or integral equivalents) are not permitted.
Without `return` or `break` switch cases have fallthrough characteristic.
```c++
// anatomy of a switch fall through
int main()
{
    switch (2)
    {
    case 1: // Does not match
        std::cout << 1 << '\n'; // Skipped
    case 2: // Match!
        std::cout << 2 << '\n'; // Execution begins here
    case 3:
        std::cout << 3 << '\n'; // This is also executed
    case 4:
        std::cout << 4 << '\n'; // This is also executed
    default:
        std::cout << 5 << '\n'; // This is also executed
    }
    
    // Intentional fall through:
    #include <iostream>
    switch (2)
    {
    case 1:
        std::cout << 1 << '\n';
        break;
    case 2:
        std::cout << 2 << '\n'; // Execution begins here
        [[fallthrough]]; // intentional fallthrough -- note the semicolon to 
        // indicate the null statement
    case 3:
        std::cout << 3 << '\n'; // This is also executed
        break;
    }

    return 0;
}
```

Stacking logical or
cases are not statements or conditions they are 'labels'
```c++
bool isVowel(char c)
{
    switch (c)
    {
    case 'a': // if c is 'a'
    case 'e': // or if c is 'e'
    case 'i': // or if c is 'i'
    case 'o': // or if c is 'o'
    case 'u': // or if c is 'u'
    case 'A': // or if c is 'A'
    case 'E': // or if c is 'E'
    case 'I': // or if c is 'I'
    case 'O': // or if c is 'O'
    case 'U': // or if c is 'U'
        return true;
    default:
        return false;
    }
}
```

#### Switch Quiz

Write a function called calculate() that takes two integers and a char representing one of the following mathematical 
operations: +, -, *, /, or % (remainder). 
Use a switch statement to perform the appropriate mathematical operation on the integers, and return the result. 
If an invalid operator is passed into the function, the function should print an error message. For the division operator, 
do an integer division, and don’t worry about divide by zero.

```c++

int calculate(int x, int y, char op)
{
    switch(op)
    {
    case '+':
        return x + y;
    case '-':
        return x - y;
    case '*':
        return x * y;
    case '/':
        return x / y;
    case '%':
        return x % y;
    default:
        std::cout << "This is an invalid operator: " << op;
        return 0;
    }
}

```
### Intro to Loops 8.8
```c++
// Q2 - ascii letters and int codes
void printLowerAscii(){

    char letter{'a'};
    
    while (letter <= 'z'){
        // this is integral promotion to integer
        std::cout << "letter: " << letter << " code: " << +letter << '\n';
        // solution from book
        std::cout << "letter: " << letter << " code: " << static_cast<int>(letter) << '\n';
        ++letter;
    } 
}

// Q2 - inversion of counters
void countPyramid(){
/*
*     // outer loops between 1 and 5
    int outer{ 1 };
    while (outer <= 5)
    {
        // For each iteration of the outer loop, the code in the body of the loop executes once

        // inner loops between 1 and outer
        // note: inner will be created and destroyed at the end of the block
        int inner{ 1 };
        while (inner <= outer)
        {
            std::cout << inner << ' ';
            ++inner;
        }

        // print a newline at the end of each row
        std::cout << '\n';
        ++outer;
    } // inner destroyed here

    return 0;
* 
* output: 
        1
        1 2
        1 2 3
        1 2 3 4
        1 2 3 4 5
* */


    int outer{ 5 };
    while (outer >= 1)
    {
        int inner{ outer };
        while (inner >= 1)
        {
            std::cout << inner << ' ';
            --inner;
        }

        // print a newline at the end of each row
        std::cout << '\n';
        --outer;
    } 

    return 0;

}

// Q4 - print like this:
/*
*       1
      2 1
    3 2 1
  4 3 2 1
5 4 3 2 1
* 
* */

void rightAlignedPyramid(){

    const int extent{5};
    int outer{1};
    
    while (extent >= outer){
        int inner{extent};
        while(inner > 0){
            if(inner <= outer)
                std::cout << inner << ' ';
            else
                std::cout << "  ";
            --inner;
        }
        std::cout << '\n';
        ++outer;
    }

}
int main(){
    printLowerAscii();
    countPyramid();
    return 0;
}

```

### 8.10 for statements

```c++
#include <iostream>


int main()
{
/* 
        1. declare and initialize variable i
        2. condition is evaluated - body of loop is executed
        3. prefix ++i is evaluated and increments i
        4. condition is evaluated - body of loop is executed
* */
    for (int i{ 1 }; i <= 10; ++i)
        std::cout << i << ' ';

    std::cout << '\n';

for (;;)
    std::cout << "stuff\n";
    
 // the above is equivalent to 
while (true)
    std::cout << "stuff\n";
    
// You can use commas for multiple variable definitions liek this. Considered acceptable

    for (int x{ 0 }, y{ 9 }; x < 10; ++x, --y)
        std::cout << x << ' ' << y << '\n';

    return 0;
}

// Q1 Write a for-loop that prints every even number from 0 to 20.

for (int i{0}; i <= 20;++i)
    std::cout << i << '\n';
    
// Q2 Write a function named sumTo() that takes an integer parameter named value, and returns the sum of all the numbers from 1 to value.

int sumTo(int val){
    int acc{}; // 0 indexed
    
    for (int i{1}; i <= val; ++i)
        acc += i;
    
    return acc;
}


// Q4 - FIZZ BUZZ
/*
* Fizz Buzz is a simple math game used to teach children about divisibility. It is also sometimes used as an interview 
* question to assess basic programming skills.
The rules of the game are simple: Starting at 1, and counting upward, replace any number divisible only by three with 
* the word “fizz”, any number only divisible by five with the word “buzz”, and any number divisible by both 3 and 5 with 
* the word “fizzbuzz”.
Implement this game inside a function named fizzbuzz() that takes a parameter determining what number to count up to. 
* Use a for-loop and a single if-else chain (meaning you can use as many else-if as you like).
The output of fizzbuzz(15) should match the following:
* 
* */

void fizzBuzz(int num){

    for (int i{1}; i <= num; ++i){
        if ( (i % 3 == 0) && (i % 5 == 0))
            std::cout << "fizzbuzz\n";
        else if (i % 3 == 0)
            std::cout << "fizz\n";        
        else if (i % 5 == 0)
            std::cout << "buzz\n";
        else
            std::cout << i << '\n';
    }

}
// Q5 - Modify the FizzBuzz program you wrote in the previous quiz to add the rule that numbers divisible by seven should be replaced with “pop”. Run the program for 150 iterations.

// In this version, using an if/else chain to explicitly cover every possible combination of words will result 
// in a function that is too long. Optimize your function so only 4 if-statements are used: one for each of the non-compound words 
// (“fizz”, “buzz”, “pop”), and one for the case where a number is printed.
void fizzBuzzMod(int num){
    for (int i{1}; i <= num; ++i){
        std::string output{};
        
        if (i % 3 == 0)
            output += "fizz";       
        if (i % 5 == 0)
            output += "buzz";
        if (i % 7 == 0)
            output += "pop";
        
        if (output.length() == 0)
            output = std::to_string(i);
       
        std::cout << output << '\n';   
    }
}
// answer from textbook is better (no string initialization)
void fizzbuzz(int count)
{
	for (int i{ 1 }; i <= count; ++i)
	{
		bool printed{ false };
		if (i % 3 == 0)
		{
			std::cout << "fizz";
			printed = true;
		}
		if (i % 5 == 0)
		{
			std::cout << "buzz";
			printed = true;
		}
		if (i % 7 == 0)
		{
			std::cout << "pop";
			printed = true;
		}

		if (!printed)
			std::cout << i;

		std::cout << '\n';
	} // end for loop
}
```
### 8.13Intro to Random Number generation

[Theoretical foundation of computer randomness!!][3]

Example of a one sequence generator
A __stateful__ function because it maintains the state of the variable across all calls of the function.

```c++
#include <iostream>

int plusOne()
{
    static int s_state { 3 }; // only initialized the first time this function is called

    // Generate the next number

    ++s_state;      // first we modify the state
    return s_state; // then we use the new state to generate the next number in the sequence
}

int main()
{
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';
    std::cout << plusOne() << '\n';

    return 0;
}
```

#### PRNG - pseudo randon number generators
Many rand generators use LCG16 like the below from the textbook. 
The below oscillates between even and odd. The other PRNGs use more state variables and complex math operations
but work the same way.
```c++
#include <iostream>
unsigned int LCG16() // our PRNG
{
    static unsigned int s_state{ 0 }; // only initialized the first time this function is called

    // Generate the next number

    // We modify the state using large constants and intentional overflow to make it hard
    // for someone to casually determine what the next number in the sequence will be.

    s_state = 8253729 * s_state + 2396403; // first we modify the state
    return s_state % 32768; // then we use the new state to generate the next number in the sequence
}

int main()
{
    // Print 100 random numbers
    for (int count{ 1 }; count <= 100; ++count)
    {
        std::cout << LCG16() << '\t';

        // If we've printed 10 numbers, start a new row
        if (count % 10 == 0)
            std::cout << '\n';
    }

    return 0;
}
```

If you run the above 3 times the SAME numbers are generated.

The initial values will determine this chain and this is  called the __random seed__.
We will need to create an algorithm to generate seed values for the PRNG to use each time.


Underseeding is limiting the number of initial seeds - thus limiting the number of random sequences that can be produced.

Consequences:
- The random sequences generated by consecutive runs may have a high correlation to each other. 
- On the generation of the Nth random number, some values will never be able to be generated. For example, a Mersenne Twister that is underseeded in a particular way will never generate the values 7 or 13 as its first output.
- Someone may be able to guess the seed based on the initial random value produced (or the first few random values). That would allow them to then generate all future random numbers that are going to be produced by the generator. This may allow them to cheat or game the system.

#### Characteristics for good seed
An ideal seed should have the following characteristics:

- The seed should contain at least as many bits as the state of the PRNG, so that every bit in the state of the PRNG can be initialized by an independent bit in the seed.
- Each bit in the seed should be independently randomized. 
- The seed should contain a good mix of 0 and 1s distributed across all of the bits.
- There should be no bits in the seed that are always 0 or always 1. These “stuck bits” do not provide any value.
- The seed should have a low correlation with previously generated seeds.

#### Characterstics of a good PRNG
1. The PRNG should generate each number with approximately the same probability.
2. The method by which the next number in the sequence is generated shouldn’t be predictable.
3. The PRNG should have a good dimensional distribution of numbers.
4. The PRNG should have a high period for all seeds - PRNGs have a period and then will repeat. This should be quite large.
5. The PRNG should be efficient

third-party libraries for more non-predictable 
The Xoshiro family and Wyrand for non-cryptographic PRNGs.
The [Chacha family][4] for cryptographic (non-predictable) PRNGs.

### 8.14 - Generating random numbers using Mersenne Twister
Mersenne Twister is used along with a number that changes each time as a seed.

Two common methods:
1. Use the System Clock
```c++
#include <iostream>
#include <random> // for std::mt19937
#include <chrono> // for std::chrono

int main()
{
	// Seed our Mersenne Twister using steady_clock
	std::mt19937 mt{ static_cast<std::mt19937::result_type>(
	// Time since the earliest time it can measure (seeds are distinct)
		std::chrono::steady_clock::now().time_since_epoch().count()
		) };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}


```
2. Use the System's Random Device
```c++

#include <iostream>
#include <random> // for std::mt19937 and std::random_device

int main()
{
	std::mt19937 mt{ std::random_device{}() };

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}

	return 0;
}
```

----> Best to use `std::random_device()`. More reliable in modern architectures than clocks


#### Seed Sequence `std::seed_seq`

Either clock or `std::random_device()` will only give us a single integer.
Instead of depleting this we can create a seed sequence that will create as many unbiased seed values. The more unviased seed
variables provided to seed sequence the better mix of 0 and 1.

```c++
#include <iostream>
#include <random>

int main()
{
	std::random_device rd{};
	std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() }; // get 8 integers of random numbers from std::random_device for our seed
	std::mt19937 mt{ ss }; // initialize our Mersenne Twister with the std::seed_seq

	// Create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };

	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 40; ++count)
	{
		std::cout << die6(mt) << '\t'; // generate a roll of the die here

		// If we've printed 10 numbers, start a new row
		if (count % 10 == 0)
			std::cout << '\n';
	}
	return 0;
}
```
### 8.15 Global Random Numbers (Random.h)

Located in header file: `./Random.h`. Very useful implementation of global random number.
Its use is here:

```c++
#include "Random.h" // defines Random::mt, Random::get(), and Random::generate()
#include <cstddef> // for std::size_t
#include <iostream>

int main()
{
	// We can call Random::get() to generate random integral values
	// If the two arguments have the same type, the returned value will have that same type.
	std::cout << Random::get(1, 6) << '\n';   // returns int between 1 and 6
	std::cout << Random::get(1u, 6u) << '\n'; // returns unsigned int between 1 and 6

        // In cases where we have two arguments with different types
        // and/or if we want the return type to be different than the argument types
        // We must specify the return type using a template type argument (between the angled brackets)
	// See https://www.learncpp.com/cpp-tutorial/function-template-instantiation/
	std::cout << Random::get<std::size_t>(1, 6u) << '\n'; // returns std::size_t between 1 and 6

	// If we have our own distribution, we can access Random::mt directly

	// Let's create a reusable random number generator that generates uniform numbers between 1 and 6
	std::uniform_int_distribution die6{ 1, 6 }; // for C++14, use std::uniform_int_distribution<> die6{ 1, 6 };
	for (int count{ 1 }; count <= 10; ++count)
	{
		std::cout << die6(Random::mt) << '\t'; // generate a roll of the die here
	}

	std::cout << '\n';

	return 0;
}
```
## 9 Testing


<!------ Links----->
[0]:https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/
[1]:https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/
[2]:https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/
[3]:https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/
[4]:https://cr.yp.to/chacha.html