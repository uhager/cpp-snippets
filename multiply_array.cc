/*  multiply_array.cc: replace every number in an array with the product of all other numbers in the array.
    author: Ulrike Hager
    date: Jul. 2016

    To compile:
    g++ -std=c++11 -Wall -o multiply_array multiply_array.cpp
*/

#include <iostream>
#include <string>
#include <cstdlib>


void brute_force(int* arr, int size, int* result)
{
  for (int i = 0; i < size; ++i ){
    result[i] = 1;
    for (int j = 0; j < size; ++j ){
      if (i == j) continue;
      result[i] *= arr[j];
    }
  }
}


void using_division(int* arr, int size, int* result)
{
  int total = 1;
  for (int i = 0; i < size; ++i ){
    total *= arr[i];
  }
  for (int i = 0; i < size; ++i ){
    result[i] = total / arr[i];
  }
}

//wrong result?
void forwards_backwards(int* arr, int size, int* result)
{
  int left_to_right[size];
  int right_to_left[size];
  left_to_right[0] = 1;
  right_to_left[size-1] = 1;
  for (int i = 1 ; i<size ; ++i) {
    left_to_right[i] = left_to_right[i-1] * arr[i-1];
  }
  for (int i = size-2 ; i>0 ; --i) {
    right_to_left[i] = right_to_left[i+1] * arr[i+1];
  }

  for (int i = 0 ; i<size ; ++i) {
    result[i] = left_to_right[i] * right_to_left[i];
  }
}



int main()
{
  int size = 0;
  std::string arr_string;
  int* arr = new int();
  int* curr = arr;

  std::cout << "Enter comma-separated array: ";
  std::getline( std::cin, arr_string );
  while (arr_string.size()) {
    std::string::size_type comma = arr_string.find_first_of(",");
    if ( comma > 0 ) {
      *curr++ = std::stoi(arr_string.substr(0,comma));
      ++size;
    }
    arr_string.erase(0,comma+1);
    if (comma == std::string::npos) break;
  }

  int result[size];

  std::cout << "Brute force: ";
  brute_force(arr, size, result);
  for (int i = 0; i<size; ++i) {
    std::cout << result[i] << ", " ;
  }
  std::cout << "\n";

  std::cout << "With division: ";
  using_division(arr, size, result);
  for (int i = 0; i<size; ++i) {
    std::cout << result[i] << ", " ;
  }
  std::cout << "\n";

  /* wrong
  std::cout << "Forwards-backwards partial products: ";
  forwards_backwards(arr, size, result);
  for (int i = 0; i<size; ++i) {
    std::cout << result[i] << ", " ;
  }
  std::cout << "\n";
  */
}
