#include "Random.h"
#include <iostream>


// QUESTION 1
// namespace Constants {
//     constexpr double gravity { 9.8 };
// }
// // Gets tower height from user and returns it
// double getTowerHeight()
// {
//     std::cout << "Enter the height of the tower in meters: ";
//     double towerHeight{};
//     std::cin >> towerHeight;
//     return towerHeight;
// }
//
// // Returns the current ball height after "seconds" seconds
// double calculateBallHeight(double towerHeight, int seconds)
// {
//
//
//     // Using formula: s = (u * t) + (a * t^2) / 2
//     // here u (initial velocity) = 0, so (u * t) = 0
//     const double fallDistance { Constants::gravity * (seconds * seconds) / 2.0 };
//     const double ballHeight { towerHeight - fallDistance };
//
//     // If the ball would be under the ground, place it on the ground
//     if (ballHeight < 0.0)
//         return 0.0;
//
//     return ballHeight;
// }
//
// // Prints ball height above ground
// void printBallHeight(double ballHeight, int seconds)
// {
//     if (ballHeight > 0.0)
//         std::cout << "At " << seconds << " seconds, the ball is at height: " << ballHeight << " meters\n";
//     else
//         std::cout << "At " << seconds << " seconds, the ball is on the ground.\n";
// }
//
// void simulateBallDescent(double towerHeight) {
//
//     double ballHeight{towerHeight};
//     for (int i{}; ballHeight > 0.0; ++i){
//         ballHeight = calculateBallHeight(ballHeight, i);
//         printBallHeight(ballHeight, i);
//     }
// }
//
// int main()
// {
//     const double towerHeight{getTowerHeight()};
//
//     simulateBallDescent(towerHeight);
//
//     return 0;
// }

// QUESTION 2
// // Make sure that assert triggers even if we compile in release mode
// #undef NDEBUG
//
// #include <cassert> // for assert
// #include <cmath>
//
//
// bool isPrimeNaive(int x)
// {
//     for (int i{2}; i < x; ++i ) {
//         if (x == 1 || x == 2 || x == 0)
//             std::exit(-1);
//         if (x % i == 0)
//             return false;
//     }
//     return true;
//     // write this function using a for loop
// }
// bool isPrime(int x) {
//     //A non-prime number (a composite number) must have at least one divisor less than or equal to its square root,
//     // so checking for divisors beyond the square root of x is unnecessary. std::sqrt(x) (in the <cmath> header)
//     //returns the square root of x.
//
//     // Test for uniques
//     if (x <= 1) return false;
//     if (x == 2) return true;
//
//     // Test for even numbers
//     if (x % 2 == 0) return false;
//
//     const double max{std::sqrt(x)};
//     // The guards are equivalent!
//     // for(int i{3}; i * i <= x; i += 2)
//     for (int i{3}; i <= max; i+=2 ){
//         if (x % i == 0)
//             return false;
//     }
//     return true;
// }
//
// int main()
// {
//     //assert(!isPrime(0)); // terminate program if isPrime(0) is true
//     // assert(!isPrime(1));
//     // assert(isPrime(2));  // terminate program if isPrime(2) is false
//     // assert(isPrimeNaive(3));
//     // assert(!isPrimeNaive(4));
//     // assert(isPrimeNaive(5));
//     // assert(isPrimeNaive(7));
//     // assert(!isPrimeNaive(9));
//     // assert(isPrimeNaive(11));
//     // assert(isPrimeNaive(13));
//     // assert(!isPrimeNaive(15));
//     // assert(!isPrimeNaive(16));
//     // assert(isPrimeNaive(17));
//     // assert(isPrimeNaive(19));
//     // assert(isPrimeNaive(97));
//     // assert(!isPrimeNaive(99));
//     // assert(isPrimeNaive(13417));
//     assert(!isPrime(0)); // terminate program if isPrime(0) is true
//      assert(!isPrime(1));
//      assert(isPrime(2));
//     assert(isPrime(3));
//     assert(!isPrime(4));
//     assert(isPrime(5));
//     assert(isPrime(7));
//     assert(!isPrime(9));
//     assert(isPrime(11));
//     assert(isPrime(13));
//     assert(!isPrime(15));
//     assert(!isPrime(16));
//     assert(isPrime(17));
//     assert(isPrime(19));
//     assert(isPrime(97));
//     assert(!isPrime(99));
//     assert(isPrime(13417));
//
//     std::cout << "Success!\n";
//
//     return 0;
// }

// Question 3 - Hi Lo game
//Implement a game of Hi-Lo. First, your program should pick a random integer between 1 and 100. The user is given 7 tries to guess the number.

// If the user does not guess the correct number, the program should tell them whether they guessed too high or too low. If the user guesses the right number, the program should tell them they won. If they run out of guesses, the program should tell them they lost, and what the correct number is. At the end of the game, the user should be asked if they want to play again. If the user doesn’t enter ‘y’ or ‘n’, ask them again.

//For this quiz, assume the user enters a valid number.

void guessControl() {

    std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is.\n";

    const int randNum{Random::get(1, 100)};
    bool correctGuess{};
    int guessNum{};
    for (int i{1}; i < 8; ++i) {
        std::cout << "Guess #"<< i <<": ";
        std::cin >> guessNum;
        if (guessNum == randNum) {

            correctGuess = true;
            break;
        }
        if (guessNum > randNum)
            std::cout << "Your guess is too high." << '\n';
        else
            std::cout << "Your guess is too low." << '\n';
    }
    if (correctGuess)
        std::cout << "Correct! You win!" << '\n';
    else
        std::cout << "Sorry, you lose. The correct number was " << randNum << ".\n";

}


int main() {

    guessControl();
    constexpr int guesses { 7 }; // the user has this many guesses
    constexpr int min     { 1 };
    constexpr int max     { 100 };
    char contAnswer{};
    while (true) {
        std::cout << "Would you like to play again (y/n)? ";
        std::cin >> contAnswer;
    switch (contAnswer) {
        case 'y': return true;
        case 'n': return false;
    }
        /* This was my solution not good.
        if (contAnswer == 'y') {
            guessControl();
        }
        if (contAnswer == 'n') {
            std::cout << "Thank you for playing" << '\n';
            break;
        } */

    }

    return 0;
}