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

Great list of [common semantic errors][5]
Interesting function pointers(using a function without its call operator `()` so `add` instead of `add()`.
Using a function’s name without calling it generally yields a function pointer holding the address of the function. Such a function pointer will implicitly convert to a bool value. And since this pointer should never have address 0, that bool value will always be true.

### 9.4 Detecting and Handling errors

__Handling Errors in Functions__

the general strategies for handling errors that occur in functions

1. Handle the error within the function
2. Pass the error back to the caller to deal with
 Passing true and fales (`std::optional` exists as a type or `std::expected`) better than a _sentinal value_ used to indicate failure and not able to correctly entered by the user for some reason
3. Halt the program - fatal aerrors
4. Throw an exception
   Use std::cout for all conventional, user-facing text.
   For an interactive program, use std::cout for normal user-facing error messages (e.g. “Your input was invalid”). Use std::cerr or a logfile for status and diagnostic information that may be helpful for diagnosing issues but probably isn’t interesting for normal users. This can include technical warnings and errors (e.g. bad input to function x), status updates (e.g. successfully opened file x, failed to connect to internet service x), percentage completion of long tasks (e.g. encoding 50% complete), etc…
   For a non-interactive program (tool or service), use std::cerr for error output only (e.g. could not open file x). This allows errors to be displayed or parsed separately from normal output.
   For any application type that is transactional in nature (e.g. one that processes specific events, such as an interactive web browser or non-interactive web server), use a logfile to produce a transactional log of events that can be reviewed later. This can include outputting to the logfile which file is being processed, updates on the percentage complete, timestamps of when it started certain stages of computing, warning and error messages, etc…

### 9.5 `std::cin` and valid input handling

__`operator>>`__
1. First, leading whitespace (spaces, tabs, and newlines at the front of the buffer) is discarded from the input buffer. This will discard any unextracted newline character remaining from a prior line of input.
2. If the input buffer is now empty, operator>> will wait for the user to enter more data. Leading whitespace is again discarded.
3. operator>> then extracts as many consecutive characters as it can, until it encounters either a newline character (representing the end of the line of input) or a character that is not valid for the variable being extracted to.

If the characters could not be extracted - C++11 assigns a 0 value and all future extractions fail until `std::cin` is cleared.

Valid Text Inputs

1. Error case 1: Extraction succeeds but input is meaningless
   - Enter a decimal number: 5 
      - Enter one of the following: +, -, *, or /: k
      - Enter a decimal number: 7
        - `5 k 7 is` 
   - Steps for input validation
     - Check whether input meets program expectations
     - If so - return value to caller
     - ELSE - tell the user something went wrong and try again.
2. Error case 2: Extraction succeeds but with extraneous input
   - Enter a decimal number: 5*7
   - with each call to `std::cin` a character is being demanded of double so it will take up to 5 leaving '*7\n' in the buffer.
   - The next call is expecting a char so will take the single '*' without waiting for the user.
   - number like above The whole program will take from the buffer and execute with the correct answe but he execution is messy.

### 9.6 Assert and `static_assert`

Semantically meangingless

```c++
void printDivision(int x, int y)
{
    if (y != 0)
        std::cout << static_cast<double>(x) / y;
    else
        std::cerr << "Error: Could not divide by zero\n";
}
```

`std::exit` - terminates a program but you lose the call stack
`std::abort` - terminates the program but give the  developer an option to continue debugging at that point by preserving the call stack.

```c++
#include <cassert>
    assert(gravity > 0.0); // This object wont reach the ground unless there is positive gravity.
```
The asserts passes silently and fails loud using `std::abort`.
```c++
// The top fails but without much description, the bottom fails but strings are always 'true' so wont affect the condition
assert(found);
/* output: Assertion failed: found, file C:\\VCProjects\\Test.cpp, line 34 */
assert(found && "Car could not be found in database");
/* output: Assertion failed: found && "Car could not be found in database", file C:\\VCProjects\\Test.cpp, line 34 */

// Used for when a case isn't needed, but when something is implemented this part of the code will fail and programmer can decide next actions.
assert(moved && "Need to handle case where student was just moved to another classroom");
```

Asserts cost runtime so you can use a macro to disable the assert in a given translation unit

`#define NDEBUG` before all any other `#include` will disable the asserts. `#undef NDEBUG` will enable it.

#### `static_assert`

Checked at compile time rather than at runtime.

Not supplied by a header include.
```c++
static_assert(condition, diagnostic_message)
static_assert(sizeof(long) == 8, "long must be 8 bytes");
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");

int main()
{
	return 0;
}

// 1>c:\consoleapplication1\main.cpp(19): error C2338: long must be 8 bytes
```

## 10 Type Conversion, Aliases and Deduction

### Type Conversion

Implicit type conversion, automatic or coercion
```c++
double d{3}; // int value implicitly converted to double.
d = 6; // int value implicitly converted to double.
double e{4.0 / 12} // 12 is implicitly converted

if (5){} // 5 is converted to a boolean - in this case true as false == 0
```
There are 5 different groups of conversions. There are 14 types of conversion in total:

| Category                  | Meaning                                              | Standard Conversion     |
|---------------------------|------------------------------------------------------|-------------------------|
| Numeric Promotions        | Small integral types to int or uint, float to double | integral float integral |
| Numeric Conversions       | Conversions taht aren't promotions (bool to int)     |                         |
| Qualification Conversions | Add or remove const or volatile from types           |                         |
| Value Transformations     | Functions to function pointer or value to object     |                         |
| Pointer Conversions       | `std::nullptr` to pointer or between pointer types   |                         |


The Compiler will produce a new value of the desired type. Otherwise failure.

```c++

void printInt(int x)
{
    std::cout << x << '\n';
}

int main()
{
    printInt(2);

    short s{ 3 }; // there is no short literal suffix, so we'll use a variable for this one
    printInt(s); // numeric promotion of short to int

    printInt('a'); // numeric promotion of char to int
    printInt(true); // numeric promotion of bool to int

    return 0;
}


// The common type between two types!
#include <type_traits>

std::common_type_t<int, double> // the common type between two types
```

#### Type Aliases

```c++
// Distance is an alias for double
using Distance = double;
typedef double Distance; // older do not use. Equivalent to the above

Distance milesToDestination{ 3.4 }; // defines a variable of type double
```
Used with preprocessers without preprocessers setting INT_2_BYTES - the bottom three will be used as type aliases.
```c++
#ifdef INT_2_BYTES
using int8_t = char;
using int16_t = int;
using int32_t = long;
#else
using int8_t = char;
using int16_t = short;
using int32_t = int;
#endif

Another use is for large cumbersome types
using VectPairSI = std::vector<std::pair<std::string, int>>; // make VectPairSI an alias for this crazy type

bool hasDuplicates(VectPairSI pairlist) // use VectPairSI in a function parameter
{
    // some code here
    return false;
}
```

#### Type Deduction / Inference
Implemented in c++ from the use of `auto`
```c++
int add(int x, int y)
{
    return x + y;
}

int main()
{
    auto d { 5.0 }; // 5.0 is a double literal, so d will be deduced as a double
    auto i { 1 + 2 }; // 1 + 2 evaluates to an int, so i will be deduced as an int
    auto x { i }; // i is an int, so x will be deduced as an int
    auto sum { add(5, 6) }; // add() returns an int, so sum's type will be deduced as an int
    
    // Type deduction doesn't pass the qualifiers 
    const int a { 5 };  // a has type const int
    const auto b { a }; // b has type const int (const dropped but reapplied)
    
    return 0;
}
```
If you want the type deduced from a string literal to be std::string or std::string_view, you’ll need to use the s or sv literal suffixes (introduced in lessons
```c++
#include <string>
#include <string_view>
    using namespace std::literals; // easiest way to access the s and sv suffixes

    auto s1 { "goo"s };  // "goo"s is a std::string literal, so s1 will be deduced as a std::string
    auto s2 { "moo"sv }; // "moo"sv is a std::string_view literal, so s2 will be deduced as a std::string_view
```
For functions you can use `auto` to have __trailing return types__.

```c++
auto add(int x, int y) -> int;
auto divide(double x, double y) -> double;
double divide(double x, double y); // equivalent
auto printSomething() -> void;
auto generateSubstring(const std::string &s, int start, int len) -> std::string;
```

#### Chapter Quiz
What type of conversion happens for each of these
```c++
int main()
{
    int a { 5 }; // 1a - no conversion needed
    int b { 'a' }; // 1b - numeric conversion - correct answer: numeric promotion 'a' to int
    int c { 5.4 }; // 1c - won't compile uniform initialisation prevents lossy conversions
    int d { true }; // 1d - numeric promotion of bool true to int
    int e { static_cast<int>(5.4) }; // 1e - no conversion needed - correct answe: numeric conversion 5.4 to int

    double f { 5.0f }; // 1f - numeric promotion float to double
    double g { 5 }; // 1g - numeric conversion int to double

    // Extra credit section
    long h { 5 }; // 1h - numeric conversion of int to long

    float i { f }; // 1i (uses previously defined variable f) - wont compile prevents narrowing conversion 
    float j { 5.0 }; // 1j - literals are doulbe - double to float num conversion
}
```
```c++
// 2a) use type aliases

#include <iostream>

namespace constants
{
    constexpr double pi { 3.14159 };
}

using Degrees = double;
using Radians = double;

Radians convertToRadians(Degrees degrees)
{
    return degrees * constants::pi / 180;
}

int main()
{
    std::cout << "Enter a number of degrees: ";
    Degrees degrees{};
    std::cin >> degrees;

    Radians radians { convertToRadians(degrees) };
    std::cout << degrees << " degrees is " << radians << " radians.\n";

    return 0;
}
```

## Chapter 11 - Function Overloading and Templates
Signature is what is used for differentiation.
Function overload differentiation:
1. Num of parameters
2. Type of parameters
3. NOT the return type
4. const or volatile
5. Ref qualifiers

_Trivial conversions_ are done conversions done to arguments to find a unique function during function overload resolution.
- lvalue to rvalue
- qual conversion (nonconst to const)
- non-ref to ref

### Deleting functions limiting overloading

When you overload you can cause certain calls to functions to halt compilation.
This is used especially when the compiler attempts to resolve a function call to a numeric conversion.

```c++
#include <iostream>

void printInt(int x)
{
    std::cout << x << '\n';
}

void printInt(char) = delete; // calls to this function will halt compilation
void printInt(bool) = delete; // calls to this function will halt compilation

int main()
{
    printInt(97);   // okay

    printInt('a');  // compile error: function deleted
    printInt(true); // compile error: function deleted

    printInt(5.0);  // compile error: ambiguous match

    return 0;
}
```
This forbids but does not remove teh function. each of the functions is a candidate for function overload resolution.

### 11.6 Function Templates

__Primary  Template__ used to generate __instantiated functions__.
Placeholder types are type template paramters 

```c++
int max(int x, int y)
{
    return (x < y) ? y : x;
}

// becomes the below with templating
/*
* Three types of template params
*   1. type template parameter - represents a type <-- most common
*   2. Non-type template param - represents a constexpr value
*   3. template template param - represents a template
* */
// There is no difference between class and typename here as keywords. 
// 'typename' is preferred as it makes it known that even fundamental types (non-class types) can be templated.
template<typename T>

T max(T x, T y) 
{
    return (x < y) ? y : x;
}
// These two are generated by the compiler with the first call of the actual signature max<int>(int, int) or double
template<>
int max<int>(int x, int y) // the generated function max<int>(int, int)
{
    return (x < y) ? y : x;
}

template<>
double max<double>(double x, double y) // the generated function max<double>(double, double)
{
    return (x < y) ? y : x;
}

/*
    <actual_type> is the template argument
*  max<actual_type>(arg1, arg2)
*   ^-- When the compiler encounters the function call max<int>(1, 2), it will determine that a function definition for 
*   max<int>(int, int) does not already exist. Consequently, the compiler will implicitly use our max<T> function 
*   template to create one.
* 
* */
int main()
{
    std::cout << max<int>(1, 2) << '\n'; // instantiates and calls function max<int>(int, int)
    std::cout << max<>(1, 2) << '\n'; // This will work for resolution
    std::cout << max(1, 2) << '\n'; // This will alsowork for resolution
    std::cout << max<double>(1, 2) << '\n'; // instantiates and calls function max<double>(double, double)
    return 0;
}
```
This process is called __function template instantiation__.
The resolution has rules as above. The difference is that if angled brackets that are empty are explicit `max<>(1, 2)`, the compiler will
only look at the template function overloads for matching signatures. If no brackets are placed this widens resolution to non-templated functions as well as templated functions like below. The compiler prefers non-templated functions in this case if there is a matching type.
```c++
#include <iostream>

template <typename T>
T max(T x, T y)
{
    std::cout << "called max<int>(int, int)\n";
    return (x < y) ? y : x;
}

int max(int x, int y)
{
    std::cout << "called max(int, int)\n";
    return (x < y) ? y : x;
}

int main()
{
    std::cout << max<int>(1, 2) << '\n'; // calls max<int>(int, int)
    std::cout << max<>(1, 2) << '\n';    // deduces max<int>(int, int) (non-template functions not considered)
    std::cout << max(1, 2) << '\n';      // calls max(int, int)

    return 0;
}
```

```c++
#include <iostream>
#include <string>

template <typename T>
T addOne(T x)
{
    return x + 1;
}

// Use function template specialization to tell the compiler that addOne(const char*) should emit a compilation error
// const char* will match a string literal
template <>
const char* addOne(const char* x) = delete;

int main()
{
    std::cout << addOne("Hello, world!") << '\n'; // compile error

    return 0;
}
```
### 11.8 Multiple Templated function

```c++
template <typename T, typename U>
auto max(T x, U y) // ask compiler can figure out what the relevant return type is
{
    return (x < y) ? y : x;
}

int main()
{
    // max<int, double>(int, double)
    std::cout << max(2, 3.5) << '\n';
    return 0;
}
```

Note ths to be usedat the `auto` keyword needs to be fully defined if it is used like above.

In the case above to have a function that can be forward declared we use the trailing return types

```c++
#include <type_traits> // for std::common_type_t

template <typename T, typename U>
auto max(T x, U y) -> std::common_type_t<T, U>;

int main()
{
    std::cout << max(2, 3.5) << '\n';

    return 0;
}

template <typename T, typename U>
auto max(T x, U y) -> std::common_type_t<T, U>
{
    return (x < y) ? y : x;
}
```

#### Abbreviated function template C++20
```c++
template <typename T, typename U>
auto max(T x, U y)
{
    return (x < y) ? y : x;
}

// equivalent with c++20
auto max(auto x, auto y)
{
    return (x < y) ? y : x;
}
```

### 11.8 Non-type template params

These can be any of the following:
- An integral type
- An enumeration type
- std::nullptr_t
- A floating point type (since C++20)
- A pointer or reference to an object
- A pointer or reference to a function
- A pointer or reference to a member function
- A literal class type (since C++20)

```c++
#include <iostream>

template <int N> // declare a non-type template parameter of type int named N
void print()
{
    std::cout << N << '\n'; // use value of N here
}
// This is instantiated by the compiler
template <>
void print<5>()
{
    std::cout << 5 << '\n';
}
int main()
{
    print<5>(); // 5 is our non-type template argument

    return 0;
}
```

Because `constexpr` are expressions evaluated at compile time, function parameters (evaluated at runtime) cannot be `constexpr`.
Non-type template params are used for these instances.

The example below converts a function that would take via its parameters a single argument that would assert ONLY at runtime
thus failing.

We want to use `static_assert()` to evaluate at compile time literals rather than at runtime. `static_assert` only takes
constexpr. A literal is a constexpr so with the use of non-type template params we are able to evaluate our literals at
compile time!!!

```c++
#include <cassert>
#include <cmath> // for std::sqrt
#include <iostream>

double getSqrt(double d)
{
    assert(d >= 0.0 && "getSqrt(): d must be non-negative");

    // The assert above will probably be compiled out in non-debug builds
    if (d >= 0)
        return std::sqrt(d);

    return 0.0;
}

int main()
{
    std::cout << getSqrt(5.0) << '\n';
    std::cout << getSqrt(-5.0) << '\n';

    return 0;
}

/*
* The above becomes!
* 
* ***/
#include <cmath> // for std::sqrt
#include <iostream>

template <double D> // requires C++20 for floating point non-type parameters
double getSqrt()
{
    static_assert(D >= 0.0, "getSqrt(): D must be non-negative");

    if constexpr (D >= 0) // ignore the constexpr here for this example
        return std::sqrt(D); // strangely, std::sqrt isn't a constexpr function (until C++26)

    return 0.0;
}

int main()
{
    std::cout << getSqrt<5.0>() << '\n';
    std::cout << getSqrt<-5.0>() << '\n';

    return 0;
}
```

### 11.9 - Quiz
```c++
// define your factorial() function template here
template <int N>
constexpr int factorial(){
    static_assert(N >= 0, "factorial input greater than or eq to 0!");
    
    int res{1};
    for (int i{2}; i <= N; ++i)
    {
        res *= i;
    }
    return res;
}

int main()
{
    static_assert(factorial<0>() == 1);
    static_assert(factorial<3>() == 6);
    static_assert(factorial<5>() == 120);

    factorial<-3>(); // should fail to compile

    return 0;
}
```
### 11.10 Using Function Templates from different files

The One Definition Rule isn't broken for inline functions or templates or types which are allowed to be defined in multiple parts of the source code if they are identically defined. 

Templates that are needed in multiple files should be defined in a header file, and then #included wherever needed. This allows the compiler to see the full template definition and instantiate the template when needed.

Example:

max.h
```c++
#ifndef MAX_H
#define MAX_H

template <typename T>
T max(T x, T y)
{
    return (x < y) ? y : x;
}

#endif
```
foo.cpp
```c++
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo()
{
	std::cout << max(3, 2) << '\n';
}
```

main.cpp
```c++
#include "max.h" // import template definition for max<T>(T, T)
#include <iostream>

void foo(); // forward declaration for function foo

int main()
{
    std::cout << max(3, 5) << '\n';
    foo();

    return 0;
}
```
## F. `constexpr`

`constexpr double circumference{ calcCircumference(3.0)};`
This either has a compile time error or if `calcCircumference()` is a constexpr function.

This function can be called in a constexpr. Because a normal function call cannot.
```c++
constexpr double calcCircumference(double radius) // now a constexpr function
{
    constexpr double pi { 3.14159265359 };
    return 2.0 * pi * radius;
}
```
Marking a function as constexpr means it can be used in a constant expression. It does not mean “will evaluate at compile-time”.

A constant expression (which may contain constexpr function calls) is only required to evaluate at compile-time in contexts where a constant expression is required.

In contexts that do not require a constant expression, the compiler may choose whether to evaluate a constant expression (which may contain constexpr function calls) at compile-time or at runtime.

A runtime (non-constant) expression (which may contain constexpr function calls or non-constexpr function calls) will evaluate at runtime.


__the likelihood that a function will actually be evaluated at compile-time as follows__:

1. Always (required by the standard):
    Constexpr function is called where constant expression is required.
    Constexpr function is called from other function being evaluated at compile-time.
2. Probably (there’s little reason not to):
    Constexpr function is called where constant expression isn’t required, all arguments are constant expressions.
3. Possibly (if optimized under the as-if rule):
    Constexpr function is called where constant expression isn’t required, some arguments are not constant expressions but their values are known at compile-time.
    Non-constexpr function capable of being evaluated at compile-time, all arguments are constant expressions.
4. Never (not possible):
    Constexpr function is called where constant expression isn’t required, some arguments have values that are not known at compile-time.

## Chapter 12 - Compound Types: References and Pointers
Types defined in terms of other existing types.

These are the following compound data types:
- Functions
- C-style Arrays
- Pointer types:
  - Pointer to object
  - Pointer to function
- Pointer to member types:
  - Pointer to data member
  - Pointer to member function
- Reference types:
  - L-value references
  - R-value references
- Enumerated types:
  - Unscoped enumerations
  - Scoped enumerations
- Class types:
  - Structs
  - Classes
  - Unions

### Value categories: lvalue and rvalue
All expressions in c++ have a type and a value category.
` auto x{ 4 / 5 }` int / int => int. 

How can compiler know which expressions can legally appear on either side of an assignment.

__Lvalue__ - left val or locator val. evaluates to an identifiable object or function (or bit-field).

```c++
    int x{};
    const double d{};

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
```
__rvalue__ - right value evaluates to a value
```c++
int return5()
{
    return 5;
}

    int x{ 5 }; // 5 is an rvalue expression
    const double d{ 1.2 }; // 1.2 is an rvalue expression

    int y { x }; // x is a modifiable lvalue expression
    const double e { d }; // d is a non-modifiable lvalue expression
    int z { return5() }; // return5() is an rvalue expression (since the result is returned by value)

    int w { x + 1 }; // x + 1 is an rvalue expression
    int q { static_cast<int>(d) }; // the result of static casting d to an int is an rvalue expression
```

__Lvalue to rvalue Conversion__

```c++
/**
*In cases where an rvalue is expected but an lvalue is provided, the lvalue will undergo an lvalue-to-rvalue conversion so that it can be used in such contexts. This basically means the lvalue is evaluated to produce its value, which is an rvalue. 
*/
int main()
{
    int x{ 1 };
    int y{ 2 };

    x = y; // y is not an rvalue, but this is legal

    return 0;
}
```
An lvalue will implicitly convert to an rvalue. This means an lvalue can be used anywhere an rvalue is expected.
An rvalue, on the other hand, will not implicitly convert to an lvalue.

### 12.3 Lvalue References

References are aliases for objects.
Lvalue references
```c++
// regular types
int        // a normal int type (not an reference)
int&       // an lvalue reference to an int object
double&    // an lvalue reference to a double object
const int& // an lvalue reference to a const int object
```
Lvalue reference varaibles! - acts a reference to an lvalue (usually another variable)
```c++
#include <iostream>

int main()
{
    int x { 5 };    // x is a normal integer variable
    // This is reference initialization
    int& ref { x }; // ref is an lvalue reference variable that can now be used as an alias for variable x

    std::cout << x << '\n';  // print the value of x (5)
    std::cout << ref << '\n'; // print the value of x via ref (5)

    return 0;
}
```
You can also use a reference to modify values:
```c++
#include <iostream>

int main()
{
    int x { 5 }; // normal integer variable
    int& ref { x }; // ref is now an alias for variable x

    std::cout << x << ref << '\n'; // print 55

    x = 6; // x now has value 6

    std::cout << x << ref << '\n'; // prints 66

    ref = 7; // the object being referenced (x) now has value 7

    std::cout << x << ref << '\n'; // prints 77

    return 0;
}
```
1. When reference is initialized it is __bound__ to that obj or function. AKA __reference binding__

2. types need to match to be initialised as reference:
   KEY::: Since the result of a conversion is an rvalue, and a non-const lvalue reference can’t bind to an rvalue, trying to bind a non-const lvalue reference to an object that does not match its referenced type will result in a compilation error.
3. Types cannot be reseated (change in what the reference refers to)
4. Referents and References have independent lives. 
    - A reference can be destroyed and the referent can continue without impediment
    - A referent can be destroyed and the reference will be left __dangling__
    - Accessing a __dangling reference__ causes undefined behaviour.
5. References aren't objects - 'variable' is a misnomer as all variables have a name and are objects.
    - a reference value is not required to edist or occupy storage. Compilers will just replace with the instance of the referent
    - No reference to a reference, because an lvalue reference must refer to an identifiable object.

#### Temporary object creation

Initializing references with an rvalue:
```c++
const int& ref { 5 }; // 5 is an rvalue
```
If you try to bind a const lvalue reference to a value of a different type, the compiler will create a temporary object of the same type as the reference, initialize it using the value, and then bind the reference to the temporary.

```c++
    char c { 'a' };
    const int& r2 { c };     // temporary int initialized with value 'a', r2 binds to temporary
```

You can remove the relationship with references by the above process by updating the original object which was decoupled 
through temporary object creation assuming it will update all references.
```c++
int main()
{
    short bombs { 1 };         // I can has bomb! (note: type is short)

    const int& you { bombs };  // You can has bomb too (note: type is int&)
    --bombs;                   // Bomb all gone

    if (you)                   // You still has?
    {
        std::cout << "Bombs away!  Goodbye, cruel world.\n"; // Para bailar la bomba
    }

    return 0;
}
/*
* In the above example, bombs is a short and you is a const int&. Because you can only bind to an int object, when you is initialized with bombs, the compiler will implicitly convert bombs to an int, which results in the creation of a temporary int object (with value 1). you ends up bound to this temporary object rather than bombs.

When bombs is decremented, you is not affected because it is referencing a different object. So although we expect if (you) to evaluate to false, it actually evaluates to true.
* */
```
Lvalue references can only bind to modifiable lvalues.

Lvalue references to const can bind to modifiable lvalues, non-modifiable lvalues, and rvalues. This makes them a much more flexible type of reference.

### 12.5 Pass by lvalue reference
```c++
#include <iostream>

void printValue(int y)
{
    std::cout << y << '\n';
} // y is destroyed here

int main()
{
    int x { 2 };

    printValue(x); // x is passed by value (copied) into parameter y (inexpensive)

    return 0;
}
```
What is occuring here is _passing by value_. A copy is made of x that forms the input to the argument.
What if we passed a reference instead? The function could be used and no copy would need to be made.

```c++
#include <iostream>

void printAddresses(int val, int& ref)
{
    std::cout << "The address of the value parameter is: " << &val << '\n';
    std::cout << "The address of the reference parameter is: " << &ref << '\n';
}

int main()
{
    int x { 5 };
    std::cout << "The address of x is: " << &x << '\n';
    printAddresses(x, x);

    return 0;
}
/*
    The address of x is: 0x7ffd16574de0
    The address of the value parameter is: 0x7ffd16574de4
    The address of the reference parameter is: 0x7ffd16574de0
*/
```
The ability for functions to modify the value of arguments passed in can be useful. Imagine you’ve written a function that determines whether a monster has successfully attacked the player. If so, the monster should do some amount of damage to the player’s health. If you pass your player object by reference, the function can directly modify the health of the actual player object that was passed in. If you pass the player object by value, you could only modify the health of a copy of the player object, which isn’t as useful.


Good practice:

Favor passing by const reference over passing by non-const reference unless you have a specific reason to do otherwise (e.g. the function needs to change the value of an argument).
Limit modifying argument values in a function.

```c++
#include <iostream>

void printRef(const int& y) // y is a const reference
{
    std::cout << y << '\n';
}

int main()
{
    int x { 5 };
    printRef(x);   // ok: x is a modifiable lvalue, y binds to x

    const int z { 5 };
    printRef(z);   // ok: z is a non-modifiable lvalue, y binds to z

    printRef(5);   // ok: 5 is rvalue literal, y binds to temporary int object

    return 0;
}
```
When to use pass by val and pass by reference:
Fundamental types and enumerated types are cheap to copy, so they are typically passed by value.
Class types can be expensive to copy (sometimes significantly so), so they are typically passed by const reference.

The following are often passed by value (because it is more efficient):

- Enumerated types (unscoped and scoped enumerations).
- Views and spans (e.g. std::string_view, std::span).
- Types that mimic references or (non-owning) pointers (e.g. iterators, std::reference_wrapper).
- Cheap-to-copy class types that have value semantics (e.g. std::pair with elements of fundamental types, std::optional, std::expected).

Pass by reference should be used for the following:
- Arguments that need to be modified by the function.
- Types that aren’t copyable (such as std::ostream).
- Types where copying has ownership implications that we want to avoid (e.g. std::unique_ptr, std::shared_ptr).
- Types that have virtual functions or are likely to be inherited from (due to object slicing concerns, covered in lesson 25.9 -- Object slicing).

#### [Comparison of Cost for Pass By Value or Pass By Reference][6]
Some highlights:
1. Each time a value parameter is used, the running program can directly access the storage location (CPU register or RAM) of the copied argument. However, when a reference parameter is used, there is usually an extra step. The running program must first directly access the storage location (CPU register or RAM) allocated to the reference, in order to determine which object is being referenced. Only then can it access the storage location of the referenced object (in RAM).
    Therefore, each use of a value parameter is a single CPU register or RAM access, whereas each use of a reference parameter is a single CPU register or RAM access plus a second RAM access.
2. For objects that are cheap to copy, the cost of copying is similar to the cost of binding, but accessing the objects is faster and the compiler is likely to be able to optimize better.
   For objects that are expensive to copy, the cost of the copy dominates other performance considerations.
3. Neet little function macro for if an object is 'cheap to copy' thus passable by value: Caveat setup costs withstanding
    ```c++
   #include <iostream>

    // Function-like macro that evaluates to true if the type (or object) is equal to or smaller than
    // the size of two memory addresses
    #define isSmall(T) (sizeof(T) <= 2 * sizeof(void*))
    
    struct S
    {
    double a;
    double b;
    double c;
    };
    
    int main()
    {
    std::cout << std::boolalpha; // print true or false rather than 1 or 0
    std::cout << isSmall(int) << '\n'; // true
    
        double d {};
        std::cout << isSmall(d) << '\n'; // true
        std::cout << isSmall(S) << '\n'; // false
    
        return 0;
    }
    ```
4. `std::string_view` or `std::string&` reference - whcih to prefer? good discussion of why `std::string_view` is faster.
   ```c++
    void doSomething(const std::string&);
    void doSomething(std::string_view);   // prefer this in most cases
    ```

### 12.7 Intro to Pointers

`char x {};`
the code generated for this definition is executed, a piece of memory from RAM will be assigned to this object. For the sake of example, let’s say that the variable x is assigned memory address 140. Whenever we use variable x in an expression or statement, the program will go to memory address 140 to access the value stored there.

#### The address-of operator (&)
```c++
int x{ 5 };
std::cout << x << '\n';  // print the value of variable x
std::cout << &x << '\n'; // print the memory address of variable x

return 0;
/*
5
0027FEA0
* */
```
For objects that use more than one byte of memory, address-of will return the memory address of the first byte used by the object.
#### The dereference operator (*)
```c++
    int x{ 5 };
    std::cout << x << '\n';  // print the value of variable x
    std::cout << &x << '\n'; // print the memory address of variable x

    std::cout << *(&x) << '\n'; // print the value at the memory address of variable x (parentheses not required, but make it easier to read)
/*
5
0027FEA0
5
* */
```

#### Definition of Pointer

A __pointer__ is an object that holds the _memory address_ typically of another variable, as its value. these are "dumb pointers"
as opposed to "smart pointers".
```c++
    int x { 5 };    // normal variable
    int& ref { x }; // a reference to an integer (bound to x)

    int* ptr;       // a pointer to an integer
    
    // Wild pointers are uninitialised pointers
    int x{ 5 };
    int* ptr;        // an uninitialized pointer (holds a garbage address)
    int* ptr2{};     // a null pointer (we'll discuss these in the next lesson)
    int* ptr3{ &x }; // a pointer initialized with the address of variable x
```
Iniitalizing a pointer with a literal val is not allowed:
```c++
int* ptr{ 5 }; // not okay
int* ptr{ 0x0012FF7C }; // not okay, 0x0012FF7C is treated as an integer literal
```

Interesting example of pointer updating
```c++
    int x{ 5 };
    int* ptr{ &x }; // initialize ptr with address of variable x

    std::cout << x << '\n';    // print x's value
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)

    *ptr = 6; // The object at the address held by ptr (x) assigned value 6 (note that ptr is dereferenced here)

    std::cout << x << '\n';
    std::cout << *ptr << '\n'; // print the value at the address that ptr is holding (x's address)
```
this prints out
```text
5
5
6
6
```
Initialize variable `x` with 5. Define pointer `ptr` with the reference to the address of variable `x`. Print x's value. 
Dereference the int pointer `ptr` to retrieve the value held at its memory address and print that value.

assign the value 6 to the address held by the pointer object. Note if this was without the dereference (`*`) operator the 
assignment of `6` would override the __address__ contianed within the object and not the value of the variable stored at that address.

When we use a pointer without a dereference (ptr), we are accessing the address held by the pointer. Modifying this (ptr = &y) changes what the pointer is pointing at.

When we dereference a pointer (*ptr), we are accessing the object being pointed at. Modifying this (*ptr = 6;) changes the value of the object being pointed at.

**Address Literals are not supported by C++**

It’s worth noting that the address-of operator (`&`) doesn’t return the address of its operand as a literal (as C++ doesn’t support address literals). Instead, it returns a pointer to the operand (whose value is the address of the operand). In other words, given variable `int x`, `&x` returns an `int*` holding the address of `x`.

```c++

int x{4};
int* ptr{ &x };
int y{ 16 };
ptr = &y; // valid - change the address of the int pointer
*ptr = 30; // valid - change the value of the variable stored at the address that is in the pointer object. y == 30 && *ptr == 30.
```

### 12.8 Null Pointers
Null pointers can be initialized through value initiatlization.

```c++
int* ptr {};
int* ptr { nullptr }; // nullptr is a keyword as a null pointer literal. Address literals do not exist in c++.
```

Dangling pointers produce undefined behaviour. The easiest way to ensure that there are none, is to ensure that any pointer 
points to a null pointer OR a valid object.

Destruction of an object still leaves pointers dangling. 

**Favour references over pointers**.Since references can’t be bound to null, we don’t have to worry about null references. 
And because references must be bound to a valid object upon creation and then can not be reseated, dangling references are harder to create.

### 12.9 Const and Pointers
1. A non-const pointer (e.g. `int* ptr`) can be assigned another address to change what it is pointing at.
2. A const pointer (e.g. `int* const ptr`) always points to the same address, and this address can not be changed.
3. A pointer to a non-const value (e.g. `int* ptr`) can change the value it is pointing to. These can not point to a const value.
4. A pointer to a const value (e.g. `const int* ptr`) treats the value as const when accessed through the pointer, and thus can not change the value it is pointing to. These can be pointed to const or non-const l-values (but not r-values, which don’t have an address).
```c++
int v{ 5 };

int* ptr0 { &v };             // points to an "int" but is not const itself.  We can modify the value or the address.
const int* ptr1 { &v };       // points to a "const int" but is not const itself.  We can only modify the address.
int* const ptr2 { &v };       // points to an "int" and is const itself.   We can only modify the value.
const int* const ptr3 { &v }; // points to a "const int" and is const itself.  We can't modify the value nor the address.

// if the const is on the left side of the *, the const belongs to the value
// if the const is on the right side of the *, the const belongs to the pointer
```

### 12.10 Pass by Address
```c++
#include <iostream>
#include <string>

void printByValue(std::string val) // The function parameter is a copy of str
{
    std::cout << val << '\n'; // print the value via the copy
}

void printByReference(const std::string& ref) // The function parameter is a reference that binds to str
{
    std::cout << ref << '\n'; // print the value via the reference
}

void printByAddress(const std::string* ptr) // The function parameter is a pointer that holds the address of str
{
    std::cout << *ptr << '\n'; // print the value via the dereferenced pointer
}

int main()
{
    std::string str{ "Hello, world!" };

    printByValue(str); // pass str by value, makes a copy of str
    printByReference(str); // pass str by reference, does not make a copy of str
    printByAddress(&str); // pass str by address, does not make a copy of str
    
    std::string* ptr { &str }; // define a pointer variable holding the address of str
    printByAddress(ptr); // pass str by address, does not make a copy of str

    return 0;
}
```
#### Testing for null pointer dereferencing

Dereferencing a null pointer within a function causes undefined behaviour. 
Two methods  could be used to avoid this:

```c++
#include <iostream>
#include <cassert>

void print(const int* ptr) // now a pointer to a const int
{
	assert(ptr); // fail the program in debug mode if a null pointer is passed (since this should never happen)

	// (optionally) handle this as an error case in production mode so we don't crash if it does happen
	if (!ptr)
		return;

	std::cout << *ptr << '\n';
}

int main()
{
	int x{ 5 };

	print(&x);
	print(nullptr);

	return 0;
}
```
### 12.13 In and out parameters

A function and its caller communicate with each other via two mechanisms: parameters and return values. When a function is called, the caller provides arguments, which the function receives via its parameters. These arguments can be passed by value, reference, or address.

This provides a way for a function to return data back to the caller in cases where using a return value is not sufficient for some reason.

__A function parameter that is used only for the purpose of returning information back to the caller is called an out parameter.__

```c++
#include <cmath>    // for std::sin() and std::cos()
#include <iostream>

// sinOut and cosOut are out parameters
void getSinCos(double degrees, double& sinOut, double& cosOut)
{
    // sin() and cos() take radians, not degrees, so we need to convert
    constexpr double pi { 3.14159265358979323846 }; // the value of pi
    double radians = degrees * pi / 180.0;
    sinOut = std::sin(radians);
    cosOut = std::cos(radians);
}
int main()
{
    double sin { 0.0 };
    double cos { 0.0 };

    double degrees{};
    std::cout << "Enter the number of degrees: ";
    std::cin >> degrees;

    // getSinCos will return the sin and cos in variables sin and cos
    getSinCos(degrees, sin, cos);

    std::cout << "The sin is " << sin << '\n';
    std::cout << "The cos is " << cos << '\n';
    return 0;
}
```
### 12.14 Type deduction pointers, references and cosnt
From the textbook Summary:
Top-level vs low-level const:

A top-level const applies to the object itself (e.g. const int x or int* const ptr).
A low-level const applies to the object accessed through a reference or pointer (e.g. const int& ref, const int* ptr).
What type deduction deduces:

Type deduction first drops any references (unless the deduced type is defined as a reference). For a const reference, dropping the reference will cause the (low-level) const to become a top-level const.
Type deduction then drops any top-level const (unless the deduced type is defined as const or constexpr).
Constexpr is not part of the type system, so is never deduced. It must always be explicitly applied to the deduced type.
Type deduction does not drop pointers.
Always explicitly define the deduced type as a reference, const, or constexpr (as applicable), and even if these qualifiers are redundant because they would be deduced. This helps prevent errors and makes it clear what your intent is.
Type deduction and pointers:

When using auto, the deduced type will be a pointer only if the initializer is a pointer. When using auto*, the deduced type is always a pointer, even if the initializer is not a pointer.
auto const and const auto both make the deduced pointer a const pointer. There is no way to explicitly specify a low-level const (pointer-to-const) using auto.
auto* const also makes the deduced pointer a const pointer. const auto* makes the deduced pointer a pointer-to-const. If these are hard to remember, int* const is a const pointer (to int), so auto* const must be a const pointer. const int* is a pointer-to-const (int), so const auto* must be a pointer-to-const)
Consider using auto* over auto when deducing a pointer type, as it allows you to explicitly reapply both the top-level and low-level const, and will error if a pointer type is not deduced.

### 12.15 `std::optional`

```c++
#include <iostream>
#include <optional> // for std::optional (C++17)

// Our function now optionally returns an int value
std::optional<int> doIntDivision(int x, int y)
{
    if (y == 0)
        return {}; // or return std::nullopt
    return x / y;
}

int main()
{
    std::optional<int> result1 { doIntDivision(20, 5) };
    if (result1) // if the function returned a value
        std::cout << "Result 1: " << *result1 << '\n'; // get the value
    else
        std::cout << "Result 1: failed\n";

    std::optional<int> result2 { doIntDivision(5, 0) };

    if (result2)
        std::cout << "Result 2: " << *result2 << '\n';
    else
        std::cout << "Result 2: failed\n";

    return 0;
}

std::optional<int> o1 { 5 };            // initialize with a value
std::optional<int> o2 {};               // initialize with no value
std::optional<int> o3 { std::nullopt }; // initialize with no value

if (o1.has_value()) // call has_value() to check if o1 has a value
if (o2)             // use implicit conversion to bool to check if o2 has a value
std::cout << *o1;             // dereference to get value stored in o1 (undefined behavior if o1 does not have a value)
std::cout << o2.value();      // call value() to get value stored in o2 (throws std::bad_optional_access exception if o2 does not have a value)
std::cout << o3.value_or(42); // call value_or() to get value stored in o3 (or value `42` if o3 doesn't have a value)
```

Prefer std::optional for optional return types.

Prefer function overloading for optional function parameters (when possible). Otherwise, use std::optional<T> for optional arguments when T would normally be passed by value. Favor const T* when T is expensive to copy.


### 12 Quiz
#### 1 - For each of the following expressions on the right side of operator <<, indicate whether the expression is an lvalue or rvalue

a. `std::cout << 5;` 5 is an rvalue. 
b. `int x { 5 }; std::cout << x;`x is an lvalue.
c. `int x { 5 }; std::cout << x + 1;` x + 1 is an rvalue. Because it evaluates to a value
d. `int foo() { return 5; } std::cout << foo();` foo() evaluates to a value so is an rvalue expression.
e. 
```c++
int& max(int &x, int &y) { return x > y ? x : y; }
int x { 5 };
int y { 6 };
std::cout << max(x, y);
```
rvalue as a max returns the value and evaluates to it??? <<-- incorrect it returns an __lvalue reference__ which is a lvalue...

#### 5
```c++
#include <iostream>
#include <algorithm>

void sort2(int& a, int& b){
    if (a > b)
        swap(a, b);
}

int main()
{
    int x { 7 };
    int y { 5 };

    std::cout << x << ' ' << y << '\n'; // should print 7 5

    sort2(x, y); // make sure sort works when values need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    sort2(x, y); // make sure sort works when values don't need to be swapped
    std::cout << x << ' ' << y << '\n'; // should print 5 7

    return 0;
}

```
<!------ Links----->
[0]:https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/
[1]:https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/
[2]:https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/
[3]:https://www.learncpp.com/cpp-tutorial/introduction-to-random-number-generation/
[4]:https://cr.yp.to/chacha.html
[5]:https://www.learncpp.com/cpp-tutorial/common-semantic-errors-in-c/
[6]:https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/