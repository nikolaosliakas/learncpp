#include <iostream>

int getValueFromUser(){

  std::cout << "Enter an integer to the program: ";
  int x{};
  std::cin>>x;

  return x;

}

int doubleNumber(int x){

  return x + x;
}

// int main(){

//   int x {getValueFromUser()};
//   int y {getValueFromUser()};

//   std::cout << x << " + " << y << " = " << x + y << '\n';

//   return 0;
// }
int main(){

  int x {getValueFromUser()};

  std::cout << "The double of " << x << " is " << doubleNumber(x)  << '\n';

  return 0;
}
