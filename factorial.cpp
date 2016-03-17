#include <iostream>

int factorial(int num)
{
  int result = 1;
  while (num){
    result *= num--;
  }
  return result;
}


int main()
{
  int num;
  std::cout << "Enter number:" ;
  std::cin >> num;

  std::cout << factorial(num) << "\n";
  
  return 0;  
}
