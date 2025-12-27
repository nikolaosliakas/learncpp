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


<!----Links here--->
[0]:https://www.learncpp.com/
[1]:https://code.visualstudio.com/docs/cpp/config-linux#_modifying-tasksjson
[2]:https://code.visualstudio.com/docs/cpp/config-linux#_cc-configurations
[3]:https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
[4]:https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/
[5]:https://www.learncpp.com/cpp-tutorial/function-return-values-value-returning-functions/
[6]:https://www.learncpp.com/cpp-tutorial/introduction-to-function-parameters-and-arguments/
[7]:https://en.cppreference.com/w/cpp/language/translation_phases.html
[8]:https://www.learncpp.com/cpp-tutorial/how-to-design-your-first-programs/
