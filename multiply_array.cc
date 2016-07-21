/*  multiply_array.cc: replace every number in an array with the product of all other numbers in the array.
    author: Ulrike Hager
    date: Jul. 2016

    To compile:
    g++ -std=c++11 -Wall -o multiply_array multiply_array.cpp
*/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <chrono>

void brute_force(const std::vector<double>& arr, double* result)
{
  for (uint32_t i = 0; i < arr.size(); ++i ){
    result[i] = 1;
    for (uint32_t j = 0; j < arr.size(); ++j ){
      if (i == j) continue;
      result[i] *= arr[j];
    }
  }
}


void using_division(const std::vector<double>& arr, double* result)
{
  double total = 1;
  for (uint32_t i = 0; i < arr.size(); ++i ){
    total *= arr.at(i);
  }
  for (uint32_t i = 0; i < arr.size(); ++i ){
    result[i] = total / arr.at(i);
  }
}


void forwards_backwards(const std::vector<double>& arr, double* result)
{
  uint32_t size = arr.size();
  double left_to_right[size];
  double right_to_left[size];
  left_to_right[0] = 1;
  right_to_left[size-1] = 1;
  for (uint32_t i = 1 ; i<size ; ++i) {
    left_to_right[i] = left_to_right[i-1] * arr[i-1];
    right_to_left[size-1-i] = right_to_left[size-i] * arr[size-i];
  }
  for (uint32_t i = 0 ; i < size ; ++i) {
    result[i] = left_to_right[i] * right_to_left[i];
  }
}


void calc_and_print(void (*fptr)(const std::vector<double>&, double*), const std::vector<double>& arr, const std::string& title = "Result")
{
  double result[arr.size()];
  std::cout << title << ": ";

  auto start_time = std::chrono::high_resolution_clock::now();
  fptr(arr, result);
  auto end_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();

  for (uint32_t i = 0; i<arr.size(); ++i) {
    std::cout << result[i] << ", " ;
  }
  std::cout << "\ntime: " << std::to_string(time) << "\n";
}


void get_input_array(std::vector<double>& arr)
{
  std::string arr_string;

  std::cout << "Enter comma-separated array: ";
  std::getline( std::cin, arr_string );

  while (arr_string.size()) {
    std::string::size_type comma = arr_string.find_first_of(',');
    if ( comma > 0 ) {
      arr.push_back( std::stod(arr_string.substr(0,comma)) );
    }
    arr_string.erase(0,comma+1);
    if (comma == std::string::npos) break;
  }

  /*
  std::cout << "read array: " ;
  for (uint32_t i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << ", " ;
  }
  */
  std::cout << "\n" ;  
}


int main()
{
  std::vector<double> arr ;

  get_input_array(arr);

  void (*methods[])(const std::vector<double>&, double*) = { brute_force, using_division, forwards_backwards};
  std::string outputs[] = {"Brute force", "With division: ", "Forwards-backwards partial products: "};

  for ( uint32_t i = 0 ; i<3; ++i ) {
    calc_and_print(*methods[i], arr, outputs[i] );
  }
}
