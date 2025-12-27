//
// Part of chapter2Quiz.cpp
//
#include <iostream>

int readNumber() {
    std::cout << "Please enter a number: \n";
    int x{};
    std::cin >> x;

    return x;
}

void writeAnswer(int input) {

    std::cout << "The answer is " << input;
}