//
// Created by N L on 27/01/2026.
//
/** 1a) What is the output of this program and why?
 *  short to int is a numeric promotion, short to double is a numeric conversion.
 *  The compiler prefers numeric promotion.
#include <iostream>

void print(int x)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    short s { 5 };
    print(s);

    return 0;
}
 1b) Why won’t the following compile?
 * The print() call to main is ambiguous because of the default argument and the other
 * overloaded function without arguments. The function overload resolution finds these ambiguous.

#include <iostream>

void print()
{
    std::cout << "void\n";
}

void print(int x=0)
{
    std::cout << "int " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5.0f);
    print();

    return 0;
}
1c) Why won’t the following compile?
* int to long or double is a numeric conversion. the compiler cannot determine which is the better numeric conversion.
*
#include <iostream>

void print(long x)
{
    std::cout << "long " << x << '\n';
}

void print(double x)
{
    std::cout << "double " << x << '\n';
}

int main()
{
    print(5);

    return 0;
}
 */

// Question 2
// step 1 - Write a function template named add() that allows the users to add 2 values of the same type.
//          The following program should run:
//
// #include <iostream>
//
// // write your add function template here
// template <typename T>
//
// T add(T x, T y) {
//     return x + y;
// }
// // step 2 - Write a function template named mult() that allows the user to multiply one value of any type (first parameter) and an integer (second parameter). The second parameter should not be a template type. The function should return the same type as the first parameter.
// template <typename T>
// T mult(T x, int y) {
//     return x * y;
// }
// // step 3 - Write a function template named sub() that allows the user to subtract two values of different types.
//
// template<typename T, typename U>
// auto sub(T x, U y) -> std::common_type_t<T, U> {
//     return x - y;
// }
//
// // Question 3 - output of this and why
// /*
//  * the program returns 1, 2 then 1, 2. At compile time T's template resolution produces two functions
//  * each with their own static int c. One with a signature count(double) and the other count(int)
//  * as these are incremented seperately with each function call matched to either.
//  */
// template <typename T>
// int count(T) // This is the same as int count(T x), except we're not giving the parameter a name since we don't use the parameter
// {
//     static int c { 0 };
//     return ++c;
// }
// int main()
// {
//     std::cout << add(2, 3) << '\n';
//     std::cout << add(1.2, 3.4) << '\n';
//
//     std::cout << mult(2, 3) << '\n';
//     std::cout << mult(1.2, 3) << '\n';
//
//     std::cout << sub(3, 2) << '\n';
//     std::cout << sub(3.5, 2) << '\n';
//     std::cout << sub(4, 1.5) << '\n';
//
//     std::cout << count(1) << '\n';
//     std::cout << count(1) << '\n';
//     std::cout << count(2.3) << '\n';
//     std::cout << count<double>(1) << '\n';
//
//     return 0;
// }
// Question 4 - output of program
#include <iostream>

int foo(int n)
{
    return n + 10;
}

template <typename T>
int foo(T n)
{
    return n;
}

int main()
{
    std::cout << foo(1) << '\n'; // #1 - calling non-template function preferred.

    short s { 2 };
    std::cout << foo(s) << '\n'; // #2 - template function using number promotion

    std::cout << foo<int>(4) << '\n'; // #3 - explicit template called

    std::cout << foo<int>(s) << '\n'; // #4 - explicit template called for s

    std::cout << foo<>(6) << '\n'; // #5 - match on templated function

    return 0;
}