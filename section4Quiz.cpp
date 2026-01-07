#include <iostream>
#include <functional>
/*
 *Q2
 *Write the following program: The user is asked to enter 2 floating point numbers (use doubles).
 *The user is then asked to enter one of the following mathematical symbols: +, -, *, or /.
 *The program computes the answer on the two numbers the user entered and prints the results.
 *If the user enters an invalid symbol, the program should print nothing.
 */

// ask for input then recursively call until input is valid


double getDoubleFromUser() {

    std::cout << "Enter a double value: ";
    double value{};

    // std::cin has a failbit!
    // The stream enters a fail state if it is passing a datatype that can't be implicitly typed
        // like 5 can be typed to 5.0 or to a char or even to a bool as non-zero true.
    // This checks that when the double value receives the input from cin that the failstate has not been triggered.

    // You must CLEAR the state - then empty the buffer before trying another read!!!!
    while (!(std::cin >> value)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid. Try again: ";
    }
    return value;
}

// Takes two doubles and returns a double!
// std::function<double(double,double)> getOperatorFromUser() {
//     std::cout << "Enter +, -, *, or /: ";
//     char op{};
//     std::cin >> op;
//
//     switch (op) {
//         case '+': return [](double x, double y){return x + y; };
//         case '-': return [](double x, double y){return x - y; };
//         case '*': return [](double x, double y){return x * y; };
//         case '/': return [](double x, double y){return x / y; };
//         default: return [](double x, double y){return 0.0;};
//     }
// }

char getOpFromUser() {
    std::cout << "Enter +, -, *, or /: ";
    char op{};
    std::cin >> op;
    if (op != '+' && op != '-' && op != '*' && op != '/') {
        std::cout << "Invalid input try again!\n";
        op = getOpFromUser();
    }
    return op;
}

void evaluateOperation(char op, double x, double y) {
    double result{};
    if (op == '+')
        result = x + y;
    else if (op == '-')
         result = x - y;
    else if (op == '/')
        result = x / y;
    else if (op == '*')
        result = x * y;
    else {
        std::cout << op << " is an invalid operator!";
        return;
    }

    std::cout << x << ' ' << op << ' ' << y << " is " << result;

}

// Question 3 functions
/*
Write a short program to simulate a ball being dropped off of a tower.
To start, the user should be asked for the height of the tower in meters.
Assume normal gravity (9.8 m/s2), and that the ball has no initial velocity (the ball is not moving to start).
Have the program output the height of the ball above the ground after 0, 1, 2, 3, 4, and 5 seconds.
The ball should not go underneath the ground (height 0).

Use a function to calculate the height of the ball after x seconds. The function can calculate how far
the ball has fallen after x seconds using the following formula:
distance fallen = gravity_constant * x_seconds^2 / 2
 */

double getBuildingHeight() {

    std::cout << "Enter the height of the tower in meters: ";
    double h{};
    while (!(std::cin >> h) || h <= 0) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid input. Try again: ";
    }
    return h;
}
double calcBallPosition(double height, double seconds) {
    return height - 9.8 * (seconds * seconds)/ 2;
}

// this is the non-iterating version I think they meant us to write
void outputCurrBallPosition(double seconds, double ballpos) {
    if (ballpos > 0)
        std::cout << "At " << static_cast<int>(seconds) << " seconds, the ball is at height: " << ballpos << " meters\n";
    else
        std::cout << "At " << static_cast<int>(seconds) << " seconds, the ball is on the ground.\n";
}
void outputBallDrop(double height) {

    outputCurrBallPosition(0, height);
    outputCurrBallPosition(1, calcBallPosition(height, 1));
    outputCurrBallPosition(2, calcBallPosition(height, 2));
    outputCurrBallPosition(3, calcBallPosition(height, 3));
    outputCurrBallPosition(4, calcBallPosition(height, 4));
    outputCurrBallPosition(5, calcBallPosition(height, 5));

}
int main(){
    // Question 2
    // double x {getDoubleFromUser()};
    // double y {getDoubleFromUser()};
    // // auto op {getOperatorFromUser()};
    // char op {getOpFromUser()};
    // evaluateOperation(op, x, y);

    // Question 3
    // get height of tower in meters
    double height = getBuildingHeight();
    outputBallDrop(height);

return 0;
}