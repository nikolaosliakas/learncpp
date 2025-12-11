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

## Chapter 0 - C++ Basics

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


<!----Links here--->
[0]:https://www.learncpp.com/
[1]:https://code.visualstudio.com/docs/cpp/config-linux#_modifying-tasksjson
[2]:https://code.visualstudio.com/docs/cpp/config-linux#_cc-configurations
[3]:https://www.learncpp.com/cpp-tutorial/variable-assignment-and-initialization/
[4]:https://www.learncpp.com/cpp-tutorial/keywords-and-naming-identifiers/
