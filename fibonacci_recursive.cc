/* fibonacci_recursive.cpp: recursively calculates Fibonacci number for a given number. 
Beware of stack overflow... 
author: Ulrike Hager
data: Jan. 2016
*/
#include <iostream>

int
fib(int n)
{
  int result;
  if (n == 0 || n == 1 )  result = 1;
  else result = fib(n-1) + fib( n-2 );
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
