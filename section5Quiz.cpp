/*
Write a program that asks for the name and age of two people, then prints which person is older.

Here is the sample output from one run of the program:

    Enter the name of person #1: John Bacon
    Enter the age of John Bacon: 37
    Enter the name of person #2: David Jenkins
    Enter the age of David Jenkins: 44
    David Jenkins (age 44) is older than John Bacon (age 37).
 */

#include <iostream>



std::string getName(int personNum) {

    std::cout << "Enter the name of person #" << personNum <<": ";
    std::string output{};
    // Use cin and do not stop at whitespace
    std::getline(std::cin >> std::ws, output);
    return output;
}
int getAge(const std::string_view name) {
    std::cout << "Enter the age of " << name << ": ";
    int age{};
    std::cin >> age;
    return age;
}
void whoIsOlder(std::string_view name1, int age1, std::string_view name2, int age2) {


    if (age1 > age2) {
        std::cout << name1 << " (age " << age1 << ") is older than " << name2 << " (age " << age2 << ").\n";

    } else {
        std::cout << name2 << " (age " << age2 << ") is older than " << name1 << " (age " << age1 << ").\n";
    }
// David Jenkins (age 44) is older than John Bacon (age 37).



}
int main(){
    const std::string p1Name{getName(1)};
    const int p1Age{getAge(p1Name)};

    const std::string p2Name{getName(2)};
    const int p2Age{getAge(p2Name)};

    whoIsOlder(p1Name, p1Age, p2Name, p2Age);

    return 0;
}