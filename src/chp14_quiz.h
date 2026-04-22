#ifndef LEARNCPP_CHP14_QUIZ_H
#define LEARNCPP_CHP14_QUIZ_H
#include <iostream>
#include <cmath>
/*
 * Q1
 * Write a class named Point2d. Point2d should contain two member variables of type double: m_x, and m_y, both defaulted to 0.0.
 */

class Point2d {
    double m_x{0.0};
    double m_y{0.0};

public:
    Point2d() = default; // needed to defaultthe defaults provided int he private member vars
    Point2d(const double x , const double y): m_x(x), m_y(y) {}

    void print() const {
        std::cout << "Point2d(" << m_x << "," << m_y << ")\n";
    }
    //std::sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2))
    double distanceTo(const Point2d& other) const{
        return std::sqrt((m_x - other.m_x) * (m_x - other.m_x) + (m_y - other.m_y) * (m_y - other.m_y));
    }
};

inline void initAndPrintPoints() {
    constexpr Point2d first{};
    const Point2d second{ 3.0, 4.0 };
    // Point2d third{ 4.0 }; // should error if uncommented
    first.print();
    second.print();

    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n';

}
#endif //LEARNCPP_CHP14_QUIZ_H