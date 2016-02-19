/* fibonacci_iterative.cpp: iteratively calculates Fibonacci number for a given number. 
author: Ulrike Hager
data: Jan. 2016
*/

#include <iostream>

int
fib(int n)
{
  int result = 1;
  if (n == 0 || n == 1 )  return result;
  
  int previous = 1;
  while (n > 1){
    int swap = result;
    result += previous;
    previous = swap;
    --n;
  }
  return result;
}

int
main()
{
  int n = 0;
  std::cout << "Enter a number: " << std::flush;
  while ( std::cin >> n ) {
    int result = fib(n);
    std::cout << "fib(" << n << ") = " << result << std::endl;
    std::cout << "Enter a number: " << std::flush;
  }
  return 0;
}
