/*
prime_factorization.cpp: calculate prime factorization for give number.
author: Ulrike Hager
date: August 2016

compile: g++ -Wall -std=c++11 -o prime_factorization prime_factorization.cpp
*/

#include <vector>
#include <string>
#include <iostream>
#include <cmath>


std::vector<int> prime_sieve(int n)
{
  std::vector<int> primes;
  std::vector<bool> checks(n+1,true);
  for ( int i = 2 ; i < std::sqrt(n) ; ++i ) {
    if (checks.at(i) == true ) {
      int k = 0;
      int j = i*i;
      while ( j+i*k <= n ) {
        checks.at(j+k*i) = false;
        ++k;
      }
    }
  }
  for ( int i = 2 ; i <=n ; ++i ) {
    if ( checks.at(i) ) primes.push_back(i);
  }
  return primes;
}



void factors(int n)
{
  std::cout << "prime factors of " << n << ": " ; 
  auto primes = prime_sieve(std::sqrt(n));
  std::vector<int> prime_factors;
  for (auto p: primes ) {
    if ( p * p  > n ) break;
      while ( n % p == 0 ) {
        prime_factors.push_back( p );
        n /= p;
      }
  }
  if ( n > 1 ) prime_factors.push_back(n);
  for ( auto i: prime_factors ) std::cout << i << ", " ;
  std::cout << "\n";
}



int main()
{
  factors(7775460);
}
