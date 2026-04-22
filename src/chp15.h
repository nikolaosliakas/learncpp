//
// Created by N L on 21/04/2026.
//

#ifndef LEARNCPP_CHP15_H
#define LEARNCPP_CHP15_H
class Calc
{
private:
    int m_value{};

public:
    Calc& add(int value) { m_value += value; return *this; }
    Calc& sub(int value) { m_value -= value; return *this; }
    Calc& mult(int value) { m_value *= value; return *this; }

    int getValue() const { return m_value; }
};

inline int calcVal(){
    Calc calc{};

    return calc.add(10).sub(3).mult(2).getValue();
}
#endif //LEARNCPP_CHP15_H