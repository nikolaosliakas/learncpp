#ifndef LEARNCPP_CHP15_5_QUIZ_H
#define LEARNCPP_CHP15_5_QUIZ_H
#include <iostream>
#include <string>

/*
 * class template named Triad that has 3 private data members with independent type template parameters.
 * The class should have a constructor, access functions, and a print() member function that is defined outside the class
 */

template <typename T, typename U, typename V>
class Triad {
    T m_a;
    U m_b;
    V m_c;
public:
    Triad(T, U, V);
    const T& first() const;
    const U& second() const;
    const V& third() const;
    void print() const;
};

// deduction guide needed for C++17 or older
template<typename T, typename U, typename V>
Triad(T, U, V) -> Triad<T, U, V>;

template<typename T, typename U, typename V>
Triad<T,U,V>::Triad(T a, U b, V c): m_a(a), m_b(b), m_c(c) {}

template<typename T, typename U, typename V>
const T& Triad<T, U, V>::first() const {
    return m_a;
}
template<typename T, typename U, typename V>
const U& Triad<T, U, V>::second() const {
    return m_b;
}
template<typename T, typename U, typename V>
const V& Triad<T, U, V>::third() const {
    return m_c;
}

template<typename T, typename U, typename V>
void Triad<T,U,V>::print() const {
    std::cout << '[' << m_a <<", "<< m_b << ", "<<m_c << "]";
}

inline int defineAndPrintTriad()
{
    Triad<int, int, int> t1{ 1, 2, 3 };
    t1.print();
    std::cout << '\n';
    std::cout << t1.first() << '\n';

    using namespace std::literals::string_literals;
    const Triad t2{ 1, 2.3, "Hello"s };
    t2.print();
    std::cout << '\n';

    return 0;
}

#endif