# Learn CPP

[learn-cpp][0] is the source of most work within this repository.

## Contents
[1. Introduction](##Intro-and-build)

## Intro and build

This is mostly for Linux as that is what is being used to do the exercises. Compiling from the command line to come.

There are different files that VSCode needs to provide settings for:

- compiler build settings -> `tasks.json`
- debugger settings -> `launch.json`
- compiler path and IntelliSense highlighting `c_cpp_properties.json`

All will be stored in the `.vscode` folder at the root.

1. [Build multiple CPP files][1]
2. [Configurations especially Builds][2]

### Compiler Configuration
`Diagnostic Error AKA error` - compiler has stopped compilation.
`Warning` not stop to compilation

## Chapter 1 - C++ Basics

### Statements and Structure of Program

1. `Statement` - instruction that causes program to _perform some actions_.
2. `Function` - a collection of statements with sequential execution.
  - every program must have a `main` function.

3. `Preprocessor Directives #include` - indicates to use the contents of the iostream library.
This line is needed for `std::cout` - character output
`<<` operator displays info on the console

```c++
// include is a preprocessor directive
#include <iostream>

int main(){

  std::cout << "Hello world!";
  return 0;

}
```

### Objects and Variables
- Hardcoded data are loaded into RAM along with the program.
- OS also allocates memory for the program to use while running.

#### Objects
Instead of direct memory access, C++ provides objects that represent a region of storage (CPU register or RAM). Objects with names are called _variables_.

#### Variables
- Variables are created by a declaration statement called a _definition_

```c++
int x; // type int variable x
```

- _Allocation_ - the process of reserving storage for objects use. This is done at runtime.


You can use single line for two different variable definitions
```c++
int a;
int b;
// equivalent
int a, b;
```

[__Initialization__][3]

To assign a value syntactically while defining the variable you can initialize it with the following:

```c++

int width {5}; // assigns the value 5 to the newly defined width.
```

There are 5 common forms of initialization in C++

```c++
int a;         // default-initialization (no initializer)

// Traditional initialization forms:
int b = 5;     // copy-initialization (initial value after equals sign)
int c ( 6 );   // direct-initialization (initial value in parenthesis)

// Modern initialization forms (preferred):
/*
  list or uniform initialisation
  Copy initialisation is hard to discern from assignment. And direct initialisation was hard to discern from function-related ops (curved braces in both cases...)
*/
int d { 7 };   // direct-list-initialization (initial value in braces)
int e {};      // value-initialization (empty braces)
```

- List initialisation also stops 'narrowing conversions'

ex:
```c++
int w1 { 4.5 }; //compile error
int w2 = 4.5; // no compile error will result in 4 in w2
int w3 (4.5) // no compile error will result in 4 in w3 copy
```

#### Unused Variables
Compiler usually complains if a variable is unused but initialised.

If you want to maintain a variable regardless of its use C++17 created the `[[maybe_unused]]` to stop the compiler from complaining
```c++

double pi { 3.14159 }; // if not used complain
[[maybe_unused]] double pi { 3.14159 }; //no complaints.
```
This also results in the compiler not using these values in the program if they have no reference.

***
NB - Default initialization `int x;` will result in indeterminate values. Value initialization `int x{};` will perform a zero-initialization.

### IOStream: cout, cin, endl

See: `./introIOStream.cpp`

### Uninitialized variables and undefined behaviour

No automatic initialization of variables to a default value (like Java).

__The default values for uninitialized variables is whatever was in the memory address before!__

    Initialized = The object is given a known value at the point of definition.
    Assignment = The object is given a known value beyond the point of definition.
    Uninitialized = The object has not been given a known value yet.

#### Undefined Behaviour

Using an uninitialized variable can cause undefined behaviour

#### Implementation defined behaviour

In some cases the standard library and a specific compiler may alter the behaviour of the standard library. This is called implementation defined behaviour.
The below may produce 4 OR 2.

```c++

#include <iostream>

int main()
{
	std::cout << sizeof(int) << '\n'; // print how many bytes of memory an int value takes

	return 0;
}
```
### Keywords and identifiers

Find 92 reserved keywords [here][4].

Best Practice for identifiers:
1. Variables - `int value;` lowercase
2. User-defined Types - Structs, Classes and enumerations start with capital.
3. Snake case or camel case (intercapped)


underscore prefaces are reserved for OS, library and compiler use.

### Intro Expressions

Programming 'expression' = sequence of literals, vars, operators or function calls.

The result of an expression is one of:

1. A value
2. An object or a function
3. Nothing (void functions non-value returning functions)


Side-effects:
1. assignment `x = 5`
2. printing to console `std::cout << x`

Expressions need to be part of a statement to execute.

### First Programs
Adding and printing: see `./section1Question3.cpp`

## Chapter 2 - Functions and Files

### Functions
1. Nested functions are not supported.
2. https://datatracker.ietf.org/doc/html/rfc3092
3. Global variables are initialised before executing `main()`


### From the [site][5]
The C++ standard only defines the meaning of 3 status codes:
0, EXIT_SUCCESS, and EXIT_FAILURE. 0 and EXIT_SUCCESS both mean
the program executed successfully. EXIT_FAILURE means the program did not
execute successfully.

EXIT_SUCCESS and EXIT_FAILURE are preprocessor macros defined in the
`<cstdlib>` header:
```c++
#include <cstdlib> // for EXIT_SUCCESS and EXIT_FAILURE

int main()
{
return EXIT_SUCCESS;
}
```

If you want to maximize portability, you should only use 0 or
EXIT_SUCCESS to indicate a successful
termination, or EXIT_FAILURE to indicate an unsuccessful termination.

### Unnamed params

"In cases where a function param needs to exist  but is not used int he boy of the function you simply omit the name." Note [here][6] states it is to maintain a calling interface to caller functions to this function. This prevents those functions from breaking when the parameter is no longer needed, but the function interface still is.

```c++
void doSomething(int count){
  // don't use count here - unreferenced parameter will throw a warning
}
```

```c++
void doSomething(int /*count*/){
  // perfectly legal function will not throw a warning. Google style requires comments in function header
}
```

### Local Scope

Parameters and declared and initialised variables are local to functions or in the local scope of reference.

- when are instantiated variables destroyed here:

```c++
int add (int x, int y){

  int z{x + y};
  return z;

}// z, y, and x destroyed here in the opposite order they were created (like a stack)
```

- class type objects will call a destructor before destruciton occurs.
- Use of objects after destruction will result in undefined behaviour.

__Lifetime is a runtime property and scope is a compile-time property__.
A local variable's lifetime ends when it goes out of scope, it is at this point that they are destroyed.



From the tutorial:

```c++
#include <iostream>

int add(int x, int y) // x and y are created and enter scope here
{
    // x and y are usable only within add()
    return x + y;
} // y and x go out of scope and are destroyed here

int main()
{
    int a{ 5 }; // a is created, initialized, and enters scope here
    int b{ 6 }; // b is created, initialized, and enters scope here

    // a and b are usable only within main()

    std::cout << add(a, b) << '\n'; // calls add(5, 6), where x=5 and y=6

    return 0;
} // b and a go out of scope and are destroyed here
```

- Execution starts at the top of main.
- main variable a is created and given value 5.
- main variable b is created and given value 6.
- Function add is called with argument values 5 and 6.
- add parameters x and y are created and initialized with values 5 and 6 respectively.
- The expression x + y is evaluated to produce the value 11.
- add copies the value 11 back to caller main.
- add parameters y and x are destroyed.
- main prints 11 to the console.
- main returns 0 to the operating system.
- main variables b and a are destroyed.


Some best-practice


When a variable is needed within a function:

- Use a function parameter when the caller will pass in the initialization value for the variable as an argument.
- Use a local variable otherwise.


#### Temporary objects
Where is the return value of `add(a, b)` stored? In a temporary object. These are destroyed at the end of the full _expression_ they are executed in. When the next statement executes they are destroyed already.

### Forward declarations

```c++
#include <iostream>
int add(int x, int y)
{
    return x + y;
}
int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}
```

If you declare you `main()` that calls `add(x,y)` sequentially above `add(x,y)` the compiler won't know abou the function add until after the main function. This is a compile error with two solutions:

1. Declare `add(x, y)` before `main()` as if stating dependencies before the dependent function
2. Use __Forward Declaration__:
```c++
#include <iostream>

int add(int x, int y);
int add(int, int); // also a valid formal declaration no need to state params

int main()
{
    std::cout << "The sum of 3 and 4 is: " << add(3, 4) << '\n';
    return 0;
}

int add(int x, int y)
{
    return x + y;
}
```

Forward declaration is used when we are referring to a function that isn't in the same file but is in the scope of the compiled program files. It can be for variables or other statements.

__Function Prototypes__ are forward declared functions.

If a forward declaration is made AND the function is called but no funciton body defined, the linker and not the compiler will raise an error:
```text
Compiling...
add.cpp
Linking...
add.obj : error LNK2001: unresolved external symbol "int __cdecl add(int,int)" (?add@@YAHHH@Z)
add.exe : fatal error LNK1120: 1 unresolved externals
```

### Declarations vs Definitions

__Declaration__ tells the compiler the existence of an identifier and its associated type info.

__Definition__ a declaration that acutally implements (function or type)or instantiates (variable) the identifier.

Definitions are a sub-type of declaration. All definitions are declarations but not the other way around.

Declarations that are not definitions are __pure declarations__ like: forward declarations.

### One Definition Rule (ODR)

1. _File_ - each function, var, type or template in a given scope can only have one definition.
2. _Program_ - each fun or var in a given scope can have only one definition.
3. _Types, Templates, Inline Functions and inline vars_ are allowed to have dup definitions in diff files so long as definitions are identical.


### `std` namespace

`cout` is defined in `std` namespace. `::` is a __scope resolution operator__. If no symbol to the left of `::` is provided then the global namespace is assumed.

An alternative to `std::cout` is to use a `using-directive` statement:

`using namespace std;` < -- brutal.


### Intro to Preprocessor
The entire process of preprocessing, compiling, and linking is called translation.

If you’re curious, [here][7] is a list of translation phases. As of the time of writing, preprocessing encompasses phases 1 through 4, and compilation is phases 5 through 7.


`#include` is a preprocessor directive


#### Macros
`#define` is the directive to create a macro.
  - a macro is a rule of how input text is converted to output text
  - 2 types: _object-like macros_ and _function-like macros_.
  - function-like macros act like functions. Their use is considered unsafe.
  - object-like macros are `#define IDENTIFIER substitution text` <-- remember this is processed BEFORE source code.
  - Recommended to avoid object-like macros with substitution text
Object-like macros __without__ substitution 
  - `#define IDENTIFIER` evaluate an identifier and do ... nothing.
  - Used for selective compilation by encircling selected code in ternery operators: `#ifdef #endif`
  - super useful as int he case below Bob like will not be compiled!
  - Conditional compilation
```c++
  #include <iostream>

#define PRINT_JOE
int main(){
#ifdef PRINT_JOE
    std::cout << "Joe\n"; // will be compiled since PRINT_JOE is defined
#endif
#ifdef PRINT_BOB
    std::cout << "Bob\n"; // will be excluded since PRINT_BOB is not defined
#endif
    return 0;}
```

Another example is the `#if 0  or #if 1`

```c++

#if 0 // Don't compile anything starting here
    std::cout << "Bob\n";
    /* Some
     * multi-line
     * comment here
     */
    std::cout << "Steve\n";
#endif // until this point
```
##### Scope of Defines

Directives are resolved before compilation. There is complete ignorance of C++ source code during this.
```c++
#include <iostream>

void foo()
{
#define MY_NAME "Alex"
}

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n';

	return 0;
}
```

Even though the directive is inside the body of `foo()`, main() will still output __My name is: Alex__.

You can `#include ` a file that can be 'copied' during preprocessing into another example: a file called `Alex.h`
```c++
#define MY_NAME "Alex"
```
Is used in `main.cpp`
```c++
#include "Alex.h" // copies #define MY_NAME from Alex.h here
#include <iostream>

int main()
{
	std::cout << "My name is: " << MY_NAME << '\n'; // preprocessor replaces MY_NAME with "Alex"

	return 0;
}
```

Only directives that are `#include`d from another file have any impact in another file.

Directives are processed and all identifiers are discarded at the end of the file, even if the file is linked. The only 
exception is the files that have been `#include`d.

### Header files

Usually you need forward declarations for use of different functionality. 
Two files use functions from a third. Adding forward declarations for functionality to two files is not a problem.
But as a source includes many more files, there needs to be a different way to use funcitonality across files.


Voila:  Header files
- allows declarations in one place and import where needed.

With forward declarations the files would look liek this:
1. add.cpp
```c++
      int add(int x, int y)
        {
        return x + y;
        }
 ```
2. main.cpp
```c++
#include<iostream>

int add(int x, int y);// forward declaration

int main()
{ std::cout<< "5 + 6 = "<< add(5, 6) << '\n'; } 
```
With header files:
1. add.h <<-- notice the `.h` ending.
```c++
// We really should have a header guard here, but will omit it for simplicity (we'll cover header guards in the next lesson)

// This is the content of the .h file, which is where the declarations go
int add(int x, int y); // function prototype for add.h -- don't forget the semicolon!
```
2. main.cpp
```c++
#include "add.h" // Insert contents of add.h at this point.  Note use of double quotes here.
#include <iostream>

int main()
{
    std::cout << "The sum of 3 and 4 is " << add(3, 4) << '\n';
    return 0;
}
```

### HeaderGuards

Your pre-processor includes two files A and B. B also includes A. If this is done in file
C. C will have two definitions of A after preprocessing. This will cause the compiler to complain.
It is good practice then to use header guards.

Header Guards allow for conditional definition headers by the _including_ file (C) only if hte preprocessor
has _not_ defined the header yet.

```c++
// square.h
#ifndef SQUARE_H
#define SQUARE_H

int getSquareSides()
{
    return 4;
}
#endif

// wave.h
#ifndef WAVE_H
#define WAVE_H

#include "square.h"

#endif

//main.cpp
#include "square.h"
#include "wave.h"

int main()
{
    return 0;
}
```

In the above, if we didn't include the header guard the preprocesser would have copied the function definition
twice and the compiler would have thrown an error.

#### `#pragma once`
This is used instead of header guards in modern c++ compilers. CLion defaults to header guards.

### First Program Design
Design Steps: [here][8].

## Chapter 4 - Fundamental Data Types
* chapter 3 was skipped as it contains debugging.

1. Each byte gets a __memory address__ 8 bits
2. Integer Types:
   - short, int, long, long long
3. Integral ('like an integer' in C++) 
   - integers, chars, bools
You can do integer operations on integrals!

8 bytes == 2^8 == 256 permutations 
Every object needs to occupy at least 1 byte. fundamental data type object sizes are found [here][9].

### SizeOf
To find the size of a particular data type you can use the `sizeof` operator.
```c++
#include <iomanip> // for std::setw (which sets the width of the subsequent output)
#include <iostream>
#include <climits> // for CHAR_BIT

int main()
{
    std::cout << "A byte is " << CHAR_BIT << " bits\n\n";

    std::cout << std::left; // left justify output

    std::cout << std::setw(16) << "bool:" << sizeof(bool) << " bytes\n";
    std::cout << std::setw(16) << "char:" << sizeof(char) << " bytes\n";
    std::cout << std::setw(16) << "short:" << sizeof(short) << " bytes\n";
    std::cout << std::setw(16) << "int:" << sizeof(int) << " bytes\n";
    std::cout << std::setw(16) << "long:" << sizeof(long) << " bytes\n";
    std::cout << std::setw(16) << "long long:" << sizeof(long long) << " bytes\n";
    std::cout << std::setw(16) << "float:" << sizeof(float) << " bytes\n";
    std::cout << std::setw(16) << "double:" << sizeof(double) << " bytes\n";
    std::cout << std::setw(16) << "long double:" << sizeof(long double) << " bytes\n";

    return 0;
}
```
This can also be used on a variable name
```c++
#include <iostream>

int main()
{
    int x{};
    std::cout << "This variable has "<< sizeof(x) <<" many bytes\n";
    return 0;
}
```

### Integers
n-bit signed variable has a range of -(2^(n-1)) to (2^(n-1))-1.

| Type	         | Minimum Size	 | Note                                      |
|---------------|---------------|-------------------------------------------|
| short int	    | 16            |                                           |
| int	          | 16            | Typically 32 bits on modern architectures |
| long int      | 32            |                                           |
| long long int | 64            |                                           |

Integer division produces a truncation of the float.
- 8/5 = 1.6 = 1 (result)

-(2^(5-1)) = -16
(2^(n-1))-1 - 15

### Booleans
```c++
// declaration
bool b ;
// inititalization

bool b1 {true};
bool b2 {false};
b1 = false;
bool b3 {}; // default is false

// logical NOT is an exclamation
bool b4 {!true}; // this will evaltuate to false
// also a function to toggle alpha rep of true/false == 1/0 is through the standard library

std::cout << std::boolalpha; // prints bools as true or false
std::cin >> std::boolalpha; // input bools as lowercase 'true' or 'false'
// this is toggled off with:
std::noboolalpha;
```

### If Statements
```c++
/*if (condition)
    true_statement;*/
 if (x == 0)
     std::cout << "The value is zero\n";
```

Truthiness exists because of the evaluation of 0 as false. Non-zero inputs as conditional expressions are treated as true
```c++
#include <iostream>

int main()
{
    int x { 4 };
    if (x) // nonsensical, but for the sake of example...
        std::cout << "hi\n";
    else
        std::cout << "bye\n";

    return 0;
}
```

The above will print 'hi' as non-zero inputs are treated as true.


### Chars

Works similar to other langs. Cool exception is the generator behaviour of `std::cin.get()`
```c++
#include <iostream>

int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin.get(ch); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';
    
    std::cin.get(ch);
    std::cout << "You entered: " << ch << '\n';
    return 0;
}

/*
* This results in:
Input a keyboard character: a b
You entered: a
You entered:  
You entered: b
* */
```
1 byte in size for char.


### Type Conversion and Casting

```c++
/*
* Implicit type conversions occur sometimes with warning of data loss ex. double to int.
* Explicit type conversions need to use the static_cast operator
* */
static_cast<target_type>(expression)

void print(int x){

    std::cout << "The number is: " << x << '\n';
}

int main(){

// implicit cast results in warning of data loss
    print(5.5);
// explicit case NO WARNING from compiler - still prints 5 as the above
    print( static_cast<int>(5.5) );
}
```

## Chapter 6 - Constants and Strings

### Constant Variables - named constants
Constant - a variable that can't be changed during program execution.

Naming conventions for constant variables

- `EARTH_GRAVITY` << c-style naming upper with underscores
- `kEarthGravity` << c++-style naming intercapped with lowercase `k` prefix.

function by-value parameters and by-balue returns should not be made constant.

`const` is a type-qualifier. That qualifies the type. There are two since 23 `const` and `volatile`.

### Literal Constants AKA unnamed constants
`float f { 4.1 }; // warning: 4.1 is a double literal, not a float literal`

- This produces a warning as 4.1 is a double and although the compiler will evaluate this, a conversion from a double to a float may result in a loss of precision. 
In these cases one would need to use the suffixes shown under teh heading 'Literal suffixes' - [here][10].
```c++
float f { 4.1f };
```

### String literals

String literals are const objects not const values! 
1. All C-style string literals have an implicit null terminator. Consider a string such as "hello". While this C-style 
string appears to only have five characters, it actually has six: 'h', 'e', 'l‘, 'l', 'o', and '\0' 
(a character with ASCII code 0). This trailing ‘\0’ character is a special character called a null terminator, 
and it is used to indicate the end of the string. A string that ends with a null 
terminator is called a null-terminated string.
2. C-style string literals are created at the beginning of the program and are constant and exist throughout the entire
program. `std::string` and `std::string_view` are temporary objects that are destroyed at the end of the expression they were created within.

### Compile time optimisation

3 + 4 - instead of evaluating the arithmatic expression each time. 7 will be evaluated during compilation and then made available to the program.

__Constant Folding__ replacing expressions with literal operands with the result of that expression. like above.

```c++
#include <iostream>

int main(){
    // int x {3 + 4}; // this has been optimised with constant folding
    int x {7};
    std::cout << x << '\n';
}
```

Another optimisation of the above is __Constant Propogation__ where the compiler replaces code with known constant values
with the values themselves. This removes the executing program to go the memory allocated to a variable to retrieve its value.

```c++
#include <iostream>

int main(){
    // int x {3 + 4}; // this has been optimised with constant folding
    // int x {7};
    std::cout << 7 << '\n';
}
```
Constant folding can also FOLLOW constant propogation
```c++
#include <iostream>

int main(){
//    int x{5};
//    int y{18};
//    
//    std::cout << x + y << '\n';
    std::cout << 5 + 18 << '\n'; // propogation
    std::cout << 23 << '\n'; // folding
}
```


#### Compile-time vs runtime constants
Literals and const objects are compile time consts.

Const function parameters and const objects whose initialisers are non-consts or runtime consts.


A constant expression is a non-empty sequence of literals, constant variables, operators, and function calls, 
all of which must be evaluatable at compile-time. The key difference is that in a constant expression, 
each part of the expression must be evaluatable at compile-time.

```c++
#include <iostream>

int getNumber()
{
    std::cout << "Enter a number: ";
    int y{};
    std::cin >> y; // can only execute at runtime

    return y;      // this return expression is a runtime expression
}

// The return value of a non-constexpr function is a runtime expression
// even when the return expression is a constant expression
int five()
{
    return 5;      // this return expression is a constant expression
}

int main()
{
   // Const integral variables with a constant expression initializer can be used in constant expressions:
   const int a { 5 };           // a is usable in constant expressions
   const int b { a };           // b is usable in constant expressions (a is a constant expression per the prior statement)
   const long c { a + 2 };      // c is usable in constant expressions (operator+ has constant expression operands)
   
   // Other variables cannot be used in constant expressions (even when they have a constant expression initializer):
   int d { 5 };                 // d is not usable in constant expressions (d is non-const)
   const int e { d };           // e is not usable in constant expressions (initializer is not a constant expression)
   const double f { 1.2 };      // f is not usable in constant expressions (not a const integral variable)
    // Literals can be used in constant expressions
    5;                           // constant expression
    1.2;                         // constant expression
    "Hello world!";              // constant expression

    // Most operators that have constant expression operands can be used in constant expressions
    5 + 6;                       // constant expression
    1.2 * 3.4;                   // constant expression
    8 - 5.6;                     // constant expression (even though operands have different types)
    sizeof(int) + 1;             // constant expression (sizeof can be determined at compile-time)

    // The return values of non-constexpr functions can only be used in runtime expressions
    getNumber();                 // runtime expression
    five();                      // runtime expression (even though the return expression is a constant expression)

    // Operators without constant expression operands can only be used in runtime expressions
    std::cout << 5;              // runtime expression (std::cout isn't a constant expression operand)

    return 0;
}
```
The likelihood that an expression is fully evaluated at compile-time can be categorized as follows:

1. Never: A non-constant expression where the compiler is not able to determine all values at compile-time.
2. Possibly: A non-constant expression where the compiler is able to determine all values at compile-time (optimized under the as-if rule).
3. Likely: A constant expression used in a context that does not require a constant expression.
4. Always: A constant expression used in a context that requires a constant expression.
w
Instead of relying on the above. We can force the compiler to expect a constexpr without inspecting the initializers of each variable.

```c++
// The return value of a non-constexpr function is not constexpr
int five()
{
    return 5;
}

int main()
{
    constexpr double gravity { 9.8 }; // ok: 9.8 is a constant expression
    constexpr int sum { 4 + 5 };      // ok: 4 + 5 is a constant expression
    constexpr int something { sum };  // ok: sum is a constant expression

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    constexpr int myAge { age };      // compile error: age is not a constant expression
    constexpr int f { five() };       // compile error: return value of five() is not constexpr

    return 0;
}

```
Any constant variable whose initializer is a constant expression should be declared as `constexpr`.

Any constant variable whose initializer is not a constant expression (making it a runtime constant) should be declared as `const`.

Caveat: In the future we will discuss some types that are not fully compatible with constexpr 
(including std::string, std::vector, and other types that use dynamic memory allocation). For constant objects of these types, 
either use const instead of constexpr, or pick a different type that is constexpr 
compatible (e.g. std::string_view or std::array).

### Intro to `std::string`

`std::getline()` does not stop at whitespace `std::cin` stops at whitespace. But it does not ignore leading whitespace.
Whitespace also includes line breaks `\n`. So if the function is called on a second input after the user has pressed return
So they entered: `2\n` --> 2 would be passed and '\n' would remain in the buffer. when std::getline() goes to extract text to name, 
it sees "\n" is already waiting in std::cin, and figures we must have previously entered an empty string!

`std::ws` - tell `>>` operator to ignore whitespace!
```c++
    std::cout << "Pick 1 or 2: ";
    int choice{};
    std::cin >> choice;

    std::cout << "Now enter your name: ";
    std::string name{};
    std::getline(std::cin >> std::ws, name); // note: added std::ws here

    std::cout << "Hello, " << name << ", you picked " << choice << '\n';

```

Avoid returning or creating parameters with `std::string` use `std::string_view` instead.

```c++
    std::cout << "foo\n";   // no suffix is a C-style string literal
    std::cout << "goo\n"s;  // s suffix is a std::string literal
```

### Intro to `string_view`

```c++
#include <iostream>
#include <string>

void printString(std::string str) // str makes a copy of its initializer
{
    std::cout << str << '\n';
}

int main()
{
    std::string s{ "Hello, world!" }; // s makes a copy of its initializer
    printString(s);

    return 0;
}
```
A new copy isn't formed
```c++
#include <iostream>
#include <string_view> // C++17

// str provides read-only access to whatever argument is passed in
void printSV(std::string_view str) // now a std::string_view
{
    std::cout << str << '\n';
}

int main()
{
    std::string_view s{ "Hello, world!" }; // now a std::string_view
    printSV(s);

    return 0;
}
```

`string_view` will not be implicitly converted to `string` - this prevents the needless copy.
To do so we need to use a static_cast

```c++

std::string_view sv{"This is a c-string literal"};

std::string s {static_cast<std::string>(sv)}; 

// you can create sv by default with the sv suffix
std::string_view sv{"This is a c-string literal"};
std::string_view sv{"This is a string_view literal"sv}; 


#include <iostream>
#include <string_view>

int main()
{
    constexpr std::string_view s{ "Hello, world!" }; // s is a string symbolic constant
    std::cout << s << '\n'; // s will be replaced with "Hello, world!" at compile-time

    return 0;
}
```

### Owners and Viewers

- `std::string` is an owner
- `std::string_view` is a viewer

Owners are copies and are free to do anything after initialization.
Viewers are not full copies and view the original object. If the original object is modified undefined behaviour can occur.
** `std::string_view` should be used for parameters to functions as there is no risk that the argument provided be it a c-string, `string` or `string_view`
is altered before the function ends.


```c++
// Misuse of string_view

#include <iostream>
#include <string>
#include <string_view>

std::string getName()
{
    std::string s { "Alex" };
    return s;
}

int main()
{
  std::string_view name { getName() }; // name initialized with return value of function
  std::cout << name << '\n'; // undefined behavior

  return 0;
}
```

In the above the return value of `getName()` needs to be used immediately or copied as the temporary value is destroyed. 
name is _dangling_ viewing an invalid object as the temporary return value has been destroyed and the memory allocated could be used by another part of the program.

Substring:
- While `std::string_view` can be used to view an entire string without making a copy, they are also useful when we want 
to view a substring without making a copy!



Things to remember about `std::string`:

- Initializing and copying std::string is expensive, so avoid this as much as possible.
- Avoid passing std::string by value, as this makes a copy.
- If possible, avoid creating short-lived std::string objects.
- Modifying a std::string will invalidate any views to that string.
- It is okay to return a local std::string by value.

Things to remember about `std::string_view`:

- std::string_view is typically used for passing string function parameters and returning string literals.
- Because C-style string literals exist for the entire program, it is always okay to set a std::string_view to a 
C-style string literal.
- When a string is destroyed, all views to that string are invalidated.
- Using an invalidated view (other than using assignment to revalidate the view) will cause undefined behavior.
- A std::string_view may or may not be null-terminated.

## Operators

All operators are assigned a level of __precedence__. This is the order in which operands are grouped.
Ex. Mult before + accesses operands.

__Associativity__ is the order of the operators (not operands). For each precedence level there is an associative direction.

Table of precedence and associativity of operators is under the subtitle [Table of operator precendence and associativity][11]


```c++
// order of argument evaluations
int main(){
    printCalculation(getValue(), getValue(), getValue()); // this line is ambiguous
/*
* The Clang compiler evaluates arguments in left-to-right order. 
* The GCC compiler evaluates arguments in right-to-left order
* */
}
```
```c++
// Questions put parentheses around order of ops

x = 3 + 4 + 5;
(3 + 4) + 5;

x = y = z;
x = (y = z); // 16 R->L

z *= ++y + 5; 
// R -> L , R -> , L -> R
z *= ( (++y)  + 5)

 a || b && c || d;
 
(a || (b && c)) || d // && has a higher precedence that || 
```

### Division
if both operands are integers it will be integer division.

You will need to static_cast to a double/float to retain the fractional output.

### Remainder and Exponentiation

```c++
// Remainder is the modulo operator %
#include <iostream>

int main(){

    std::cout << 2 % 4; // the result is 2 integer division 0 with 2 as a remainder. 
    
    std::cout << -4 % 2;; // result is -2 - the remainder operator always returns with the sign of the left hand term.
    std::cout << 4 % -2;; // result is 2 - the remainder operator always returns with the sign of the left hand term.
    
    
    return 0;
}
```

#### Exponentiation

`^` - This is the bitwise XOR in c++.

This is how you evaluate exponents.
```c++
#include <cmath>
double x{std::pow(3.0, 4.0); // 3.0 raised to the 4.0 power. 
```

Below is integer exponentiation. Which may be prefered because `pow()` has return and param signatures of double and may be inaccurate.
This is done by exponentiation by squaring algo.
```c++
#include <cassert> // for assert
#include <cstdint> // for std::int64_t
#include <iostream>

// note: exp must be non-negative
// note: does not perform range/overflow checking, use with caution
/*
* 
* The constexpr specifier allows a function to be evaluated at compile-time if used in a constant expression; 
* otherwise, 
* it behaves like a regular function and is evaluated at runtime.*/
constexpr std::int64_t powint(std::int64_t base, int exp)
{
	assert(exp >= 0 && "powint: exp parameter has negative value");

	// Handle 0 case
	if (base == 0)
		return (exp == 0) ? 1 : 0;

	std::int64_t result{ 1 };
	while (exp > 0)
	{
		if (exp & 1)  // if exp is odd
			result *= base;
		exp /= 2;
		base *= base;
	}

	return result;
}

int main()
{
	std::cout << powint(7, 12) << '\n'; // 7 to the 12th power

	return 0;
}
```
### incement decrement
Because of the extra steps of post fixing, prefer prefixing in your code
```c++
#include <iostream>

int main(){
    int x {5};
    int y {++x}; // x is incremented to 6, x is evaluated to 6, 6 is assigned to y.
    int y {x++}; // x is incremented to 6, copy of original x is evaluated to value 5, 5 is assigned to y.
    
    return 0;
}
```

#### Side effects
1. change a value of an object
2. i/o
3. updating a graphical interface

sequencing of side effects is not prescriptive in the standard.
```c++
x + ++x; // this is an unspecified behaviour
/*
* gcc and visStudio produce 2 + 2;
* clang produces 1 + 2;
* */
```
### Conditional operator
`condition  ? true_branch : false_branch `
This can be used in places statements cannot like initialization

```c++
constexpr bool inBigClassroom{true};
constexpr int classSize{ inBigClassroom ? 50 : 20 }; // this is allowed
constexpr int classSize{ if(inBigClassroom) 50; else 20; }; // This would not be allowed

// This also will not compile as it is viewed as if it has not been defined!
// **** Variables defined in if-else also die like those defined in functions.
    if (inBigClassroom)
        constexpr int classSize { 30 };
    else
        constexpr int classSize { 20 };
```

### Floating point comparisons
How to compare floating points

Method 1: distance between a and b is less than the tolerated distance
```c++
#include <cmath> // for std::abs()

// absEpsilon is an absolute value
bool approximatelyEqualAbs(double a, double b, double absEpsilon)
{
    // if the distance between a and b is less than or equal to absEpsilon, then a and b are "close enough"
    return std::abs(a - b) <= absEpsilon;
}
```

Method 2: Knuth Art of computer programming vol II - Seminumerical algorithms
Similar to distance but related to the magnitude of a and b.
```c++
#include <algorithm> // for std::max
#include <cmath>     // for std::abs

// Return true if the difference between a and b is within epsilon percent of the larger of a and b
bool approximatelyEqualRel(double a, double b, double relEpsilon)
{
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}
```

explanation [here][12] // Very important link.

Before c++23 you cannot make the above or constexpr qualifier as it `std::abs` was only made `constexpr` in c++23.
There is a fix at the link above.




<!----Links here--->
VERY COOL LINK -----> https://wandbox.org can test anything here!
[0]:https://www.learncpp.com/
[1]:https://code.visualstudio.com/docs/cpp/config-linux#_modifying-tasksjson
[2]:https://code.visualstudio.com/docs/cpp/config-linux#_cc-configurations
[3]:https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
[4]:https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/
[5]:https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/
[6]:https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/
[7]:https://en.cppreference.com/w/cpp/language/translation_phases.html
[8]:https://www.learncpp.com/cpp-tutorial/how-to-design-your-first-programs/
[9]:https://www.learncpp.com/cpp-tutorial/object-sizes-and-the-sizeof-operator/
[10]:https://www.learncpp.com/cpp-tutorial/literals/
[11]:https://www.learncpp.com/cpp-tutorial/operator-precedence-and-associativity/
[12]:https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
