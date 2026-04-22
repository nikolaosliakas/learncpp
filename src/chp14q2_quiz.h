#ifndef LEARNCPP_CHP14q2_QUIZ_H
#define LEARNCPP_CHP14q2_QUIZ_H
#include <iostream>

class Fraction {
    int m_numerator{0};
    int m_denominator{1};

public:
    Fraction() = default;
    Fraction(const int numer, const int denom)
        : m_numerator{numer}, m_denominator{denom}{}

    Fraction multiply(const Fraction& other) const {
        return {m_numerator * other.m_numerator,
                m_denominator * other.m_denominator
        };}
    void printFraction() {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }

    void getFraction() {
        std::cout << "Enter a value for numerator: ";
        std::cin >> m_numerator; // this is a member function, so we can access members directly
        std::cout << "Enter a value for denominator: ";
        std::cin >> m_denominator;
        std::cout << '\n';
    }
};
inline int initAndPrintFraction()
{
    Fraction f1{};
    f1.getFraction();
    Fraction f2{};
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";
    f1.multiply(f2).printFraction();

    return 0;
}
#endif