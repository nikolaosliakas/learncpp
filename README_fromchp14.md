# Notes continued from README starting at [Chapter 14][0]

## 14 Intro to Classes

Structs can have member functions like classes. They are unified except for _constructors_. This is a special
member function that only classes can have.

```c++

struct Date
{
    int day{};
    int month {};
    int year{};
    
    void print(){
        std::cout << year << '-' << month << '-' << day;
    }
};

int main(){
    
    Date today {13, 02, 2026}; // if this was class the list initialiser would try to trigger a constructor Date(d, m, y){};
    today.print();
     
    return 0;
}
```
__Use a `namespace` if a struct has no data members__


__questions__ <br>
Create a struct called IntPair that holds two integers. 
Add a member function named print that prints the value of the two integers.

```c++
#include <iostream>

struct IntPair{
    int first{};
    int second{};
    
    void print(){
        std::cout << "The first value is: " << first << '\n';
        std::cout << "The second value is: " << second << '\n';
    }
    bool isEqual(IntPair& iPair){
        return (first == iPair.first) && (second == iPair.second);
    }
};

int main()
{
	IntPair p1 {1, 2};
	IntPair p2 {3, 4};

	std::cout << "p1: ";
	p1.print();

	std::cout << "p2: ";
	p2.print();

	std::cout << "p1 and p1 " << (p1.isEqual(p1) ? "are equal\n" : "are not equal\n");
	std::cout << "p1 and p2 " << (p1.isEqual(p2) ? "are equal\n" : "are not equal\n");

	return 0;
}
```
### 14.4 const member functions

You cannot call a non-const member function from a constant class object, even if the function isn't trying to modify the data members.

A `const member function` is a member function that guarantees it will not modify the object or call any non-const member 
functions (as they may modify the object).

### 14.5 Public and private members and access levels

`m_` is used to distinguish member variables (especially without the implicit `this`). The same is customary with `g_` for 
globals and `s_` for static identifiers.

Classes have their data members private by default. Structs have them public by defaults. Classes are not aggregate types
because they require that all members are not private.

#### Quiz 2a
Write a class named Point3d. The class should contain:
- Three private member variables of type int named m_x, m_y, and m_z;
- A public member function named setValues() that allows you to set values for m_x, m_y, and m_z.
- A public member function named print() that prints the Point in the following format: <m_x, m_y, m_z>
```c++
#include <iostream>

class Point3d{

private:
    int m_x{};
    int m_y{};
    int m_z{};
public:
    void setValues(int x, int y, int z){
        m_x = x;
        m_y = y;
        m_z = z;
    }
    void print(){
        std::cout << "<" << m_x << ", " << m_y << ", " << m_z << ">\n";
    }
    int get_mx(){
        return m_x;
    }
    int get_my(){
        return m_y;
    }
    int get_mz(){
        return m_z;
    }
    bool isEqual(Point3d& otherPoint){
        // ACCESS controls work on a 'per class' not 'per object' basis so the below is redundant.
        return (m_x == otherPoint.get_mx()) && (m_y == otherPoint.get_my()) && (m_z == otherPoint.get_mz());
        // THIS is the correct way below:
        return (m_x == otherPoint.m_x) && (m_y == otherPoint.m_y) && (m_z == otherPoint.m_z);
    }
}; 

int main(){
	Point3d point1{};
	point1.setValues(1, 2, 3);

	Point3d point2{};
	point2.setValues(1, 2, 3);

	std::cout << "point 1 and point 2 are" << (point1.isEqual(point2) ? "" : " not") << " equal\n";

	Point3d point3{};
	point3.setValues(3, 4, 5);

	std::cout << "point 1 and point 3 are" << (point1.isEqual(point3) ? "" : " not") << " equal\n";


    return 0;
}
```

Recommended to declare public members first then private.
This is google's style guide approach:
- Types and type aliases (typedef, using, enum, nested structs and classes, and friend types)
- Static constants 
- Factory functions 
- Constructors and assignment operators 
- Destructor 
- All other functions (static and non-static member functions, and friend functions)
- Data members (static and non-static)

### 14.9 14.10 constructors

```c++
#include <iostream>

class Foo
{
private:
    int m_x {};
    int m_y {};

public:
    Foo(int x, int y)
        : m_x { x }, m_y { y } // here's our member initialization list
    {
        std::cout << "Foo(" << x << ", " << y << ") constructed\n";
    }

    void print() const
    {
        std::cout << "Foo(" << m_x << ", " << m_y << ")\n";
    }
};

int main()
{
    Foo foo{ 6, 7 };
    foo.print();

    return 0;
}

```

#### Questions
Write a class named Ball. Ball should have two private member variables, one to hold a color, and one to hold a radius. Also write a function to print out the color and radius of the ball.
```c++
#include <iostream>

class Ball{

public: 
    Ball(double radius)
        : Ball{default_color, radius}
        {}
    Ball(std::string_view color = default_color, double radius = default_radius)
        : m_color{color}
        , m_radius{radius}
        {
            print();
        }
    const std::string& getColor() const{
        return m_color;
    }
    double getRadius() const{
        return m_radius;
    }

    
private:
    static constexpr std::string_view default_color{ "black" };
    static constexpr double default_radius{ 10.0 };
    std::string m_color{};
    double m_radius{};
    void print() const {
    std::cout << "Ball(" << m_color << ", " << m_radius << ")" << '\n';
    }
    

};

void print(const Ball& ball) {
    std::cout << "Ball(" << ball.getColor() << ", " << ball.getRadius() << ")" << '\n';
    }

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };
    
//    print(def);
//    print(blue);
//    print(twenty);
//    print(blueTwenty);
    
    return 0;
}
```


### 14.2 Delegated Constructors
Instead of calling one constructor from another member function (constructor to create your final construction)
you can _delegate_ constructors using the list construction. It is common to have the constructor with fewer parameters delegate to the constructor with more parameters.
```c++
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    std::string m_name { "???" };
    int m_id { 0 };

public:
    Employee(std::string_view name)
        : Employee{ name, 0 } // delegate initialization to Employee(std::string_view, int) constructor
    {
    }

    Employee(std::string_view name, int id)
        : m_name{ name }, m_id { id } // actually initializes the members
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1{ "James" };
    Employee e2{ "Dave", 42 };
}
```

You can use defaulted arguments rather than delegeted constructors. Best to use defaulted arguments.

**Constants can be made using the `static constexpr` inside the classes that then can be used as a default in constructor parameter**
```c++

#include <iostream>
#include <string>
#include <string_view>

class Employee
{
private:
    static constexpr int default_id { 0 }; // define a named constant with our desired initialization value

    std::string m_name {};
    int m_id { default_id }; // we can use it here

public:

    Employee(std::string_view name, int id = default_id) // and we can use it here
        : m_name { name }, m_id { id }
    {
        std::cout << "Employee " << m_name << " created\n";
    }
};

int main()
{
    Employee e1 { "James" };
    Employee e2 { "Dave", 42 };
}

```
#### Quiz
Question 1 - Add 4 constructors, one to handle each case below:
```c++

class Ball{

public: 
    Ball(double radius)
        : Ball{default_color, radius}
        {}
    Ball(std::string_view color = default_color, double radius = default_radius)
        : m_color{color}
        , m_radius{radius}
        {}
    
private:
    static constexpr std::string_view default_color{ "black" };
    static constexpr double default_radius{ 10.0 };
    std::string m_color{};
    double m_radius{};
    

};

void print(Ball& ball) {
    std::cout << "Ball(" << ball.getColor() << ", " << ball.getRadius() << ")" << '\n';
    }

int main()
{
    Ball def{};
    Ball blue{ "blue" };
    Ball twenty{ 20.0 };
    Ball blueTwenty{ "blue", 20.0 };
    
    print(def);
    print(blue);
    print(twenty);
    print(blueTwenty);
    
    return 0;
}
```

### 14.13 Temporary Class objects

You don't need to define a separate variable for single use of a created object. 

```c++
void print(IntPair ip){
    
    std::cout << "(" << ip.first << ", " << ip.second << ")" << '\n';
}

int main(){

    IntPair iPair{1, 8};
    print(iPair); // case 1 - create variable then pass to function
    
    print(IntPair {1, 8}) // case 2 - construct anaonymous object of IntPair type and pass to function.
    
    print({1, 8}) // case 3 - implicit conversion to temporary IntPair and pass to function.
    
    return 0;
}
```
As a quick rule of thumb: Prefer static_cast when converting to a fundamental type, and a list-initialized temporary when converting to a class type.

Prefer static_cast when to create a temporary object when any of the following are true:

    We need to performing a narrowing conversion.
    We want to make it really obvious that we’re converting to a type that will result in some different behavior (e.g. a char to an int).
    We want to use direct-initialization for some reason (e.g. to avoid list constructors taking precedence).

Prefer creating a new object (using list initialization) to create a temporary object when any of the following are true:

    We want to use list-initialization (e.g. for the protection against narrowing conversions, or because we need to invoke a list constructor).
    We need to provide additional arguments to a constructor to facilitate the conversion.
```c++
// printString.h
#include <string>
void printString(const std::string &s)
{
    std::cout << s << '\n';
}

// main.cpp
#include "printString.h"
#include <iostream>
#include <string>
#include <string_view>

int main()
{
    std::string_view sv { "Hello" };

    // We want to print sv using the printString() function

//    printString(sv); // compile error: a std::string_view won't implicitly convert to a std::string

    printString( static_cast<std::string>(sv) ); // Case 1: static_cast returns a temporary std::string direct-initialized with sv
    printString( std::string { sv } );           // Case 2: explicitly creates a temporary std::string list-initialized with sv
    printString( std::string ( sv ) );           // Case 3: C-style cast returns temporary std::string direct-initialized with sv (avoid this one!)

    return 0;
}
```
### 14.14 Copy Constructor

```c++
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // What constructor is used here?
    // This constructor is not calling the default or a particular program defined constructor
        // It is calling the COPY constructor!!
        // This can be program defined OR implictly created by C++
        // Default behaviour is member-wise initialisation. 
            // f.m_numerator --> fCopy.m_numerator

    f.print();
    fCopy.print();
/*

        Fraction(5, 3)
        Fraction(5, 3)
* */
```

Program defined copy constructor looks like this:
```c++
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    // Default constructor
    Fraction(int numerator=0, int denominator=1)
        : m_numerator{numerator}, m_denominator{denominator}
    {
    }

    // Copy constructor
    Fraction(const Fraction& fraction)
        // Initialize our members using the corresponding member of the parameter
        : m_numerator{ fraction.m_numerator }
        , m_denominator{ fraction.m_denominator }
    {
        std::cout << "Copy constructor called\n"; // just to prove it works
    }

    void print() const
    {
        std::cout << "Fraction(" << m_numerator << ", " << m_denominator << ")\n";
    }
};

int main()
{
    Fraction f { 5, 3 };  // Calls Fraction(int, int) constructor
    Fraction fCopy { f }; // Calls Fraction(const Fraction&) copy constructor

    f.print();
    fCopy.print();

    return 0;
}
```

**You should prefer the implicit copy constructor and not define your own**
- The compiler may remove the copy constructor so reliance on any other behaviour than copying is unreliable.

#### Pass and Return by value
If an object is passed by value the copy constructor is called!
Return by value is the same process where a temporary copy is returned. This is done by invoking the copy constructor.

You can use the `delete` keyword to prevent the copy constructor from being used.
The rule of three is a well known C++ principle that states that if a class requires a user-defined copy constructor, destructor, or copy assignment operator, then it probably requires all three. In C++11, this was expanded to the rule of five, which adds the move constructor and move assignment operator to the list.


### 14.15 Class inititalisation adn copy elision

```c++
#include <iostream>

class Foo
{
public:

    // Default constructor
    Foo()
    {
        std::cout << "Foo()\n";
    }

    // Normal constructor
    Foo(int x)
    {
        std::cout << "Foo(int) " << x << '\n';
    }

    // Copy constructor
    Foo(const Foo&)
    {
        std::cout << "Foo(const Foo&)\n";
    }
};

int main()
{
    // Calls Foo() default constructor
    Foo f1;           // default initialization
    Foo f2{};         // value initialization (preferred)

    // Calls foo(int) normal constructor
    Foo f3 = 3;       // copy initialization (non-explicit constructors only)
    Foo f4(4);        // direct initialization
    Foo f5{ 5 };      // direct list initialization (preferred)
    Foo f6 = { 6 };   // copy list initialization (non-explicit constructors only)

    // Calls foo(const Foo&) copy constructor
    Foo f7 = f3;      // copy initialization
    Foo f8(f3);       // direct initialization
    Foo f9{ f3 };     // direct list initialization (preferred)
    Foo f10 = { f3 }; // copy list initialization

    return 0;
}
```
NB - list initialisation prevents narrowing conversions

__Copy Elision__ is when the compiler elides calling the copy constructor. This is why you shouldn't have side effects if you choose to implement a custom copy-constructor.

### 14.16 Converting constructor and the `explicit` keyword

All constructors are converting constructors by default. 

```c++

class Dollars
{
private:
    int m_dollars{};
    
public:
    Dollars(int d)                  // FOCUS here.
        : m_dollars{d}
        {}
    int getDollars() const {return m_dollars; }
     
}
void print(Dollars d)
{
    std::cout << "$" << d.getDollars();
}

int main()
{
    print(5); // not clear from intent that the conversion would happen with `Dollars(int)` constructor
    
    return 0;
}
```

You can use the `explicit` keyword to prevent the constructor from being a conversion constructor.
```c++

class Dollars
{
private:
    int m_dollars{};
    
public:
    explicit Dollars(int d)                  // FOCUS here.
        : m_dollars{d}
        {}
    int getDollars() const {return m_dollars; }
     
}
```
The above would cause the main function to have a compile error when calling print as this conversion can't occur.

**You should usually make constructors with single arguments explicit**

### 14.17 constexpr aggregates and classes
The below
start with calling `p.greater()` as a const expression.
THEN the Pair object p was not a constexpr. Then the error that although `p` was a literal (evaluatable at compile-time) its type was not. this is where the constructor was then qualified as `constexpr`. 
```c++
#include <iostream>

class Pair
{
private:
    int m_x {};
    int m_y {};

public:
    constexpr Pair(int x, int y): m_x { x }, m_y { y } {} // now constexpr

    constexpr int greater() const
    {
        return (m_x > m_y  ? m_x : m_y);
    }
};

int main()
{
    constexpr Pair p { 5, 6 };
    std::cout << p.greater() << '\n';

    constexpr int g { p.greater() };
    std::cout << g << '\n';

    return 0;
}
```
### 14.x

```c++

#include <iostream>
#include <cmath> // std::sqrt

class Point2d{

public:
    Point2d(double x=0.0, double y=0.0)
    : m_x{x}
    , m_y{y}
    {}
    
    void print(){
        std::cout << "Point2d(" << m_x << ", " << m_y << ")\n";
    }
    double distanceTo(const Point2d& otherPoint){
        return std::sqrt(
                    (m_x - otherPoint.m_x)*(m_x - otherPoint.m_x) 
                    + (m_y - otherPoint.m_y)*(m_y - otherPoint.m_y)
                    );
    }
    
    
private:
    double m_x{};
    double m_y{};


};

int main()
{
    Point2d first{};
    Point2d second{ 3.0, 4.0 };

    // Point2d third{ 4.0 }; // should error if uncommented

    first.print(); // Question 1
    second.print(); // Question 1
    std::cout << "Distance between two points: " << first.distanceTo(second) << '\n'; // Question 2
    return 0;
}

```

Question 3 - conversion of non-member functions to member functions

```c++
#include <iostream>

class Fraction
{
private:
    int m_numerator{ 0 };
    int m_denominator{ 1 };

public:
    explicit Fraction(int numerator=0, int denominator=1)
        : m_numerator { numerator }, m_denominator { denominator}
    {
    }

    void getFraction()
    {
        std::cout << "Enter a value for numerator: ";
        std::cin >> m_numerator; // this is a member function, so we can access members directly
        std::cout << "Enter a value for denominator: ";
        std::cin >> m_denominator;
        std::cout << '\n';
    }

    Fraction multiply(const Fraction& f) const
    {
        return Fraction{ m_numerator * f.m_numerator, m_denominator * f.m_denominator };
    }

    void printFraction() const
    {
        std::cout << m_numerator << '/' << m_denominator << '\n';
    }
};

int main()
{
    Fraction f1{};
    f1.getFraction();

    Fraction f2{};
    f2.getFraction();

    std::cout << "Your fractions multiplied together: ";

    f1.multiply(f2).printFraction();

    return 0;
}
```

## Chapter 15 - More on Classes

### 15.1 `this` pointer
```c++
#include <iostream>

class Simple
{
private:
    int m_id{};

public:
    Simple(int id)
        : m_id{ id }
    {
    }

    int getID() const { return m_id; }
    void setID(int id) { m_id = id; }

    void print() const { std::cout << m_id; }       // implicit use of this
    void print() const { std::cout << this->m_id; } // explicit use of this
    // (*this).m_id
};

int main()
{
    Simple simple{1};
    simple.setID(2);

    simple.print();

    return 0;
}
```

In the above, `simple.setID(2)` actually has two arguments. The rewritten expression is:
```c++
Simple::setID(simple&, 2); // changed from an object prefix to a function argument

void setID(int id) { m_id = id; }
static void setID(Simple* const this, int id) { this->m_id = id; }
```
Notice the method is actually a static method accepting an object pointer to an instance of the class `this` keyword. 

#### Returning `this`

Function chaining requires the return of this. Since the output of one function can be used to chain AKA pipe results from one to another.
Example without chaining:
```c++
class Calc
{
public:
    
    void add(int value){ m_value += value;}
    void sub(int value){ m_value -= value;}
    void mult(int value){ m_value *= value;}
    
    int getValue() const {return m_value;}
private:
    int m_value{};

}
int main(){
    
    Calc calc{};
    calc.add(5); // returns void
    calc.sub(3); // returns void
    calc.mult(4); // returns void

    std::cout << calc.getValue() << '\n';
    return 0;
}
```
And with chaining returning a reference class object
```c++
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
int main()
{
    Calc calc{};
    calc.add(5).sub(3).mult(4); // method chaining

    std::cout << calc.getValue() << '\n';

    return 0;
}
```

#### Resetting a class object
Returning an object to its 'default' state uses a reset member function
```c++
void reset()
{
    *this = {}; // value initialize a new object and overwrite the implicit object
}

```

### 15.2 Classes and Header Files

Classes get large. 
Header files contain the full definition of the class, rather than just the forward declaration (like functions).
1. Prefer to put your class definitions in a header file with the same name as the class. Trivial member functions (such as access functions, constructors with empty bodies, etc…) can be defined inside the class definition.

2. Prefer to define non-trivial member functions in a source file with the same name as the class.
```c++

// Date.h
#ifndef DATE_H
#define DATE_H

class Date
{
private:
    int m_year{};
    int m_month{};
    int m_day{};

public:
    Date(int year, int month, int day);

    void print() const;

    int getYear() const { return m_year; }
    int getMonth() const { return m_month; }
    int getDay() const { return m_day; }
};

#endif 

// Date.cpp
#include "Date.h"

Date::Date(int year, int month, int day) // constructor definition
    : m_year{ year }
    , m_month{ month }
    , m_day{ day }
{
}

void Date::print() const // print function definition
{
    std::cout << "Date(" << m_year << ", " << m_month << ", " << m_day << ")\n";
};
```
In the two files `Date.h` and `Date.cpp` we have the definitions and the scope resolution operators on the function name. This allows us to define __member functions__ and __constructors__ outside the class definitions!!


#### Inline member functions
Member functions defined outside a class are not inline and will break the ODR if `#include`-d in multiple files (thus defined in multiple translation units, rather than defined in one place). Member functions defined inside a class are implicitly `inline`.
Prefix your member functions defined outside the class to have this capability if desired.

#### Header and Class definitions and Code files
Very long-winded discussion around compilation time increasing because changes to headers will require all included definitions to be recompiled (which may take hours).

this __whole__ discussion is circumvented with:

Third, in modern C++, classes or libraries are increasingly being distributed as “header-only”, meaning all of the code for the class or library is placed in a header file. This is done primarily to make distributing and using such files easier, as a header only needs to be #included, whereas a code file needs to be explicitly added to every project that uses it, so that it can be compiled. If intentionally creating a header-only class or library for distribution, all non-trivial member functions can be made inline and placed in the header file beneath the class definition.

### 15.3 Nested types
Nested types are often public.
The enumerator is an unscoped enumerator because its scope region is the class.
```c++
#include <iostream>

class Fruit
{
public:
	// FruitType has been moved inside the class, under the public access specifier
        // We've also renamed it Type and made it an enum rather than an enum class
	enum Type
	{
		apple,
		banana,
		cherry
	};

private:
	Type m_type {};
	int m_percentageEaten { 0 };

public:
	Fruit(Type type) :
		m_type { type }
	{
	}

	Type getType() { return m_type;  }
	int getPercentageEaten() { return m_percentageEaten;  }

	bool isCherry() { return m_type == cherry; } // Inside members of Fruit, we no longer need to prefix enumerators with FruitType::
};

int main()
{
	// Note: Outside the class, we access the enumerators via the Fruit:: prefix now
	Fruit apple { Fruit::apple };

	if (apple.getType() == Fruit::apple)
		std::cout << "I am an apple";
	else
		std::cout << "I am not an apple";

	return 0;
}
```
Aliases are used for deyp definitions

```c++
#include <iostream>
#include <string>
#include <string_view>

class Employee
{
public:
    using IDType = int; // useful in aliasing types that may expand later

private:
    std::string m_name{};
    IDType m_id{};
    double m_wage{};

public:
    Employee(std::string_view name, IDType id, double wage)
        : m_name { name }
        , m_id { id }
        , m_wage { wage }
    {
    }

    const std::string& getName() { return m_name; }
    IDType getId() { return m_id; } // can use unqualified name within class
};

int main()
{
    Employee john { "John", 1, 45000 };
    Employee::IDType id { john.getId() }; // must use fully qualified name outside class

    std::cout << john.getName() << " has id: " << id << '\n';

    return 0;
}
```
### 15.4 Destructors intro

1. The destructor must have the same name as the class, preceded by a tilde (~).
2. The destructor can not take arguments.
3. The destructor has no return type.

Destructors can call other member functions (because this is done BEFORE object is destroyed)
This is the output of the following program

    Constructing Simple 1
    Constructing Simple 2
    Destructing Simple 2
    Destructing Simple 1
```c++
#include <iostream>

class Simple
{
private:
    int m_id {};

public:
    Simple(int id)
        : m_id { id }
    {
        std::cout << "Constructing Simple " << m_id << '\n';
    }

    ~Simple() // here's our destructor
    {
        std::cout << "Destructing Simple " << m_id << '\n';
    }

    int getID() const { return m_id; }
};

int main()
{
    // Allocate a Simple
    Simple simple1{ 1 };
    {
        Simple simple2{ 2 };
    } // simple2 dies here

    return 0;
} // simple1 dies here
```

### 15.5 Class Templates
```c++
#include <iostream>
#include <string>

template <typename T, typename U, typename V>
class Triad
{
public:
    // When we define a member function inside the class definition,
    // the template parameter declaration belonging to the class applies
    Triad(const T& first, const U& second, const V& third)
    : m_first{first}
    , m_second{second}
    , m_third{third} {}
    
    T first() const { return m_first; }
    U second() const { return m_second; }
    V third()const { return m_third; }
    
    void print() const; // declaration always!!!
private:
    T m_first{};
    U m_second{};
    V m_third{};
}; 

template <typename T, typename U, typename V>
void Triad<T, U, V>::print() const {
    std::cout   << "[" 
                << m_first 
                << ", " << m_second 
                << ", " << m_third << "]\n";
}

int main()
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

```
### 15.4 Static member variables

```c++
#include <iostream>

class Something
{
private:
    static inline int s_idGenerator { 1 }; // make static mem variables inline or constexpr to be initialised INSIDE of the class defintiion
    int m_id {};

public:
    // grab the next value from the id generator
    Something() : m_id { s_idGenerator++ }
    {
    }

    int getID() const { return m_id; }
};

int main()
{
    Something first{};
    Something second{};
    Something third{};

    std::cout << first.getID() << '\n';
    std::cout << second.getID() << '\n';
    std::cout << third.getID() << '\n';
    return 0;
}
```
Best practice is to use the class name and the scope resolution operator to access static variables
This is because all objects the class SHARE the static variable

```c++
Something::s_value
// use the above instead of 
Something first{};
first.s_value{};
```

```c++
/*Question #1

Convert the Random namespace in the following example to a class with static members:
* */
#include <chrono>
#include <random>
#include <iostream>

namespace Random
{
	inline std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

	// Generate a random int between [min, max] (inclusive)
	inline int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}
}

class Random
{
private: // could be public if we want these to be accessible
	static std::mt19937 generate()
	{
		std::random_device rd{};

		// Create seed_seq with high-res clock and 7 random numbers from std::random_device
		std::seed_seq ss{
			static_cast<std::seed_seq::result_type>(std::chrono::steady_clock::now().time_since_epoch().count()),
				rd(), rd(), rd(), rd(), rd(), rd(), rd() };

		return std::mt19937{ ss };
	}

	static inline std::mt19937 mt{ generate() }; // generates a seeded std::mt19937 and copies it into our global object

public:
	// Generate a random int between [min, max] (inclusive)
	static int get(int min, int max)
	{
		return std::uniform_int_distribution{min, max}(mt);
	}
};


int main()
{
	// Print a bunch of random numbers
	for (int count{ 1 }; count <= 10; ++count)
		std::cout << Random::get(1, 6) << '\t';

	std::cout << '\n';

	return 0;
}
From the book
```
## Chapter 16 - Containers, Arrays and Dynamic Arrays (Lists) `std::vector`

C++ containers are implmented as class templates to allow for users to provide type arguments.

Array Types in C++:
1. __C-style arrays__
2. `std::vector` - container class
3. `std::array` - container class

### 16.2 Intro do `std::vector`
```c++
#include <vector>

int main()
{
	// List construction (uses list constructor)
	std::vector<int> primes{ 2, 3, 5, 7 };          // vector containing 4 int elements with values 2, 3, 5, and 7
	std::vector vowels { 'a', 'e', 'i', 'o', 'u' }; // vector containing 5 char elements with values 'a', 'e', 'i', 'o', and 'u'.  Uses CTAD (C++17) to deduce element type char (preferred).

	return 0;
}
```
- Arrays are always contiguous in memory
```c++
#include <iostream>
#include <vector>

int main()
{
    std::vector primes { 2, 3, 5, 7, 11 }; // hold the first 5 prime numbers (as int)

    std::cout << "An int is " << sizeof(int) << " bytes\n";
    std::cout << &(primes[0]) << '\n';
    std::cout << &(primes[1]) << '\n';
    std::cout << &(primes[2]) << '\n';

    return 0;
}
```
This outputs:

        An int is 4 bytes
        00DBF720
        00DBF724
        00DBF728

- Creating an array of `n` length
```c++

std::vector<int> data { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // vector containing 10 int values
// equivalent with explicit constructor 
//          explicit std::vector<T>(std::size_t)
std::vector<int> data( 10 ); // vector containing 10 int elements, value-initialized to 0
```

- Creating a member of a class of `std::vector` with some default initial value
```c++
struct Foo
{
    std::vector<int> v{ std::vector<int>(8) }; // ok
}; 
```

1. Define a `std::vector` using CTAD and initialize it with the first 5 positive square numbers (1, 4, 9, 16, and 25).
    ```c++
    #include <vector>
    
    int main(){
    
        std::vector squares{1, 4, 9, 16, 25}; // CTAD will determine the <int> template argument
    }
    ```
2. Difference semantically between the two
    ```c++
    std::vector<int> v1 { 5 }; // list initialisation - creates an array with a single int element with value 5
    std::vector<int> v2 ( 5 ); // direct initialisation - creates an array with 5 int elements
    ```
3. Define a std::vector (using an explicit template type argument) to hold the high temperature (to the nearest tenth of a degree) for each day of a year (assume 365 days in a year).
   ```c++
   std::vector<double> dailyHigh(365);
   ```
   
4. Using a std::vector, write a program that asks the user to enter 3 integral values. Print the sum and product of those values.

The output should match the following:
```c++
//Enter 3 integers: 3 4 5
//The sum is: 12
//The product is: 60
#include <iostream>


std::vector<int> getThreeInts(){
    std::vector<int> threeInts(3);
    std::cout << "Enter 3 integers: ";
    std::cin >> threeInts[0] >> threeInts[1] >> threeInts[2];

    return threeInts;
}

void print(std::vector<int> intVector){

    std::cout << "The sum is: "
    << std::reduce(intVector.begin(), intVector.end(), 0, [](const int a, int b){return a + b;})
    << '\n';
    std::cout << "The product is: "
    << std::reduce(intVector.begin(), intVector.end(), 1, [](int a, int b){return a * b;})
    << '\n';
}


int main(){

    print( getThreeInts() );
}
```
### 16.3 size of 

```c++
/*
* std::size() is a non-member function that returns a `size_type` not an int.
* 
* */
#include <iostream>
#include <vector>

int main()
{
    std::vector prime { 2, 3, 5, 7, 11 };
    std::cout << "length: " << std::size(prime); // C++17, returns length as type `size_type` (alias for `std::size_t`)
    /*
* 
* std::ssize() - is the signed version that of std::ptrdiff_t which is the 
*               signed counterpart to std::size_t which is a type with UNSIGNED type
* */
    // These are two ways to use length as an int
    int length { static_cast<int>(std::ssize(prime)) }; // static_cast return value to int
    auto length { std::ssize(prime) }; // use auto to deduce signed type, as returned by std::ssize()

    return 0;
}
```

Bounds checking.

The `operator[]` does not bounds checking. The `.at()` member function does runtime bounds checking. It throws an exception that needs to be handled. the second is slower, but safer. the `operator[]` is used more often as bound validity is either checked or guaranteed in some way before checking an invalid index.

The simplest thing to do in this case is use a variable of type std::size_t as your index, and do not use this variable for anything but indexing. That way you’ll avoid any non-constexpr conversions in the first place.More info with indexing in 16.7.

Questions:
1. Initialize a std::vector with the following values: ‘h’, ‘e’, ‘l’, ‘l’, ‘o’. Then print the length of the array (use std::size()). Finally, print the value of the element with index 1 using the subscript operator and the at() member function.

   The program should output the following:
      - The array has 5 elements.
      - ee
   ```c++
   #include <iostream>
   #include <vector>
   
   int main(){
        std::vector word {'h', 'e', 'l', 'l', 'o'};
        std::cout << "The array has " << std::size(arr) << " elements \n";
        std::cout << word[1] << word.at(1) << '\n'
   }
   ```


<!------ Links----->
[0]:https://www.learncpp.com/cpp-tutorial/introduction-to-object-oriented-programming/