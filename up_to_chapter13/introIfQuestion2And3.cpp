//
// Created by N L on 07/01/2026.
//

#include <iostream>


bool validateInput(int n) {
    if (n > 9) {
        std::cout << "The number is two large\n";
        return false;
    }
    if (n < 0) {
        std::cout << "The number is too small\n";
        return false;
    }
        return true;
}

int getInput(){

    int x{};
    std::cout << "Input a number between 0 and 9: ";

    std::cin >> x;
    if (validateInput(x))
        return x;
    return getInput();
}
std::string isPrime(int y) {
    int primes[4] = {2, 3, 5, 7};

    // for (int i = 0; i < 4; i++) {
    //     if (n == primes[i])
    //         return true;
    // }
    // since c++ 11
    for (int num : primes) {
        if (y == num)
            return " is ";
    }
    return " is not ";
}

int main() {

    std::cout << "The number you input " << isPrime(getInput()) << " prime!";

    return 0;

}