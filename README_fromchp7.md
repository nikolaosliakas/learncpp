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


<!------ Links----->
[0]:https://www.learncpp.com/cpp-tutorial/compound-statements-blocks/
[1]:https://www.learncpp.com/cpp-tutorial/inline-functions-and-variables/
[2]:https://www.learncpp.com/cpp-tutorial/scope-duration-and-linkage-summary/