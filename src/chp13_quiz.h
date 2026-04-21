//
// Created by N L on 20/04/2026.
//

#ifndef LEARNCPP_CHP13_QUIZ_H
#define LEARNCPP_CHP13_QUIZ_H
// https://www.learncpp.com/cpp-tutorial/chapter-13-summary-and-quiz/

#include <iostream>
#include <string>
/*
 * 1/ Declare a struct that represents your monster. The monster should have a type that can be one of the following:
 * an ogre, a dragon, an orc, a giant spider, or a slime
 * Write a function named printMonster() that prints out all of the struct’s members. Instantiate an ogre and a slime,
initialize them using an initializer list, and pass them to printMonster().
 *
 */
enum MonsterType {
    ogre = 1,
    dragon = 2,
    orc = 3,
    giant_spider = 4,
    slime = 5
};

struct Monster {
    MonsterType monster_t;
    std::string name;
    int health;
};

struct CorrectMonster{
    enum Type {
        ogre,
        dragon,
        orc,
        giant_spider,
        slime
    };
};

constexpr  std::string monsterTypeToString(const MonsterType& monsterType) {

    switch (monsterType) {
        case ogre : {return "ogre";
            break;
        }
        case dragon :{return "dragon";
            break;}
        case orc : {return "orc";
            break;
        }
        case giant_spider :{return "dragon";
            break;}
        case slime :{ return "slime";
            break;}

    };
    return "Unknown";

}

inline void printMonster(const Monster& monster) {

    std::cout << "This " << monsterTypeToString(monster.monster_t) << " is named "
    << monster.name << " and has "<< monster.health
        << " health.\n";
}
inline void createAndPrintMonsters() {
    const Monster Torg{ogre, "Torg", 145};
    const Monster Blurp{slime, "Blurp", 23};
    printMonster(Torg);
    printMonster(Blurp);
}

template<typename T>
class Triad {

    T m_a;
    T m_b;
    T m_c;
public:
    Triad(T a, T b, T c) :
    m_a(a), m_b(b), m_c(c){}

    T getA() {return m_a;}
    T getB() {return m_b;}
    T getC() {return m_c;}
};

template<typename T>
void printTriad(Triad<T>& triad) {

    std::cout <<'[' << triad.getA() << ", " << triad.getB() << ", " << triad.getC() << ']';
}

inline void initAndPrintTriads() {
    Triad t1{ 1, 2, 3 };
    printTriad(t1);

    Triad t2{ 1.2, 3.4, 5.6 };
    printTriad(t2);

}

#endif //LEARNCPP_CHP13_QUIZ_H