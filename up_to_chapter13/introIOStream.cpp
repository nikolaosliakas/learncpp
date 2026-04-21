#include <iostream>



void oneNum(){
  std::cout << "Enter a number:  "; // asks for num

  int x{}; // value-initialize variable for user input
  std::cin >> x;

  std::cout << "If I increment 1 to: " << x << " I get " << x + 1 << '\n';
}

void twoNums(){
  std::cout << "Enter two nums seperated by a space :  "; // asks for num

  int x{};
  int y{};
  std::cin >> x >> y;

  std::cout << "You entered : " << x << " and " << y << '\n';
}

void threeNums(){
    std::cout << "Enter three nums seperated by a space :  "; // asks for num

  int x{};
  int y{};
  int z{};
  std::cin >> x >> y >> z;

  std::cout << "You entered : " << x << " and " << y << " and "<< z  << '\n';
}
int main(){


  threeNums();

  return 0;

}
