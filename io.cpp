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


int main()
{
    std::cout << "Input a keyboard character: "; // assume the user enters "a b" (without quotes)

    char ch{};
    std::cin.get(ch); // extracts a, leaves " b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch); // extracts space, leaves "b\n" in stream
    std::cout << "You entered: " << ch << '\n';

    std::cin.get(ch);
    std::cout << "You entered: " << ch << '\n';
    return 0;
}