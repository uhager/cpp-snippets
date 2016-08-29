/* fibonacci_log.cpp: iteratively calculates Fibonacci number for a given number. Takes a shortcut by jumping /2 every even number. 
author: Ulrike Hager
data: Aug. 2016
*/


#include <iostream>
#include <vector>

typedef unsigned long long ull;
typedef std::vector<ull> row;
typedef std::vector<row> matrix;


void print_matrix(matrix m)
{
  std::cout << "{ ";
  for ( unsigned int i = 0; i < m.size() ; ++i ) {
    if ( i > 0 ) std::cout << ", ";
    std::cout << "{" ;
    for ( unsigned int j = 0 ; j < m.at(i).size() ; ++j ) {
      if ( j > 0 ) std::cout << ", " ;
      std::cout << m.at(i).at(j);
    }
    std::cout << "}";
  }
  std::cout << "}";
}



matrix multiply_matrices(matrix a, matrix b)
{
  matrix result;
  unsigned int rows = a.size();
  unsigned int columns = b.at(0).size();
  unsigned int a_cols = b.size();  // b must have as many rows as a has columns -> = a.at(0).size()
  for (unsigned int i = 0 ; i < rows ; ++i ) {
    result.push_back( row( columns ) ) ;
    row current_row = a.at(i);
    for ( unsigned int j = 0; j < columns ; ++j) {
      ull sum = 0;
      for ( unsigned int k = 0 ; k < a_cols ; ++k) {
	sum += current_row.at(k) * b.at(k).at(j);
      }
      result.at(i).at(j) = sum;
    }
  }
   // print_matrix( result );
   // std::cout << "\n";
  return result;
}
  


ull fib(int n)
{
  matrix init{ {1,1} , {1,0} };
  matrix values{ {1} , {0} };
  matrix adj = init;
  
  while ( n > 0 ) {
    if ( n % 2 == 0 ) {
      adj = multiply_matrices(adj,adj);
      n /= 2;
    }
    else{ 
      values = multiply_matrices( adj, values );
      --n;
    }
  }
  return values.at(0).at(0);
}


int main()
{
  int n = 0;
  std::cout << "Enter a number: " << std::flush;
  while ( std::cin >> n ) {
    ull result = fib(n);
    std::cout << "fib(" << n << ") = " << result << std::endl;
    std::cout << "Enter a number: " << std::flush;
  }
  return 0;
}
