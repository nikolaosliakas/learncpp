#include <iostream>

int add (int, int);

int main(){

  std::cout << "Enter a number: ";
  int x{};
  std::cin >> x;

  std::cout << "Double the number " << x << " is " << add(x, x) << '\n';

  return 0;

}
