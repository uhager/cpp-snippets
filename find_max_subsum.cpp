/*  find_max_subsum.cpp: find the largest possible sum of a contiguous subarray in a given array.
    author: Ulrike Hager
    date: Jul. 2016

    To compile:
    g++ -Wall -std=c++11 -o find_max_subsum find_max_subsum.cpp
*/

#include <iostream>
#include <vector>
#include <string>


int32_t determine_max_sum(const std::vector<int32_t>& array)
{
  int32_t max_sum = 0;
  int32_t current_sum = 0;

  for (auto i: array){
    current_sum = ( current_sum + i > 0 ) ? current_sum + i : 0;
    if ( current_sum > max_sum ) max_sum = current_sum;
  }
  return max_sum;
}


std::vector<int32_t> get_array()
{
  std::vector<int32_t> result;
  
  std::string str_array;
  std::cout << "Enter array of integers: " ;
  std::getline( std::cin, str_array );

  while ( str_array.size() ) {
    std::string::size_type comma_position = str_array.find_first_of(",");
    result.push_back( std::stoi( str_array.substr(0, comma_position) ) );
    str_array.erase( 0, comma_position+1 );
    if (comma_position == std::string::npos ) break;
  }
  return result;
}


int main()
{
  auto array = get_array();
  auto result = determine_max_sum( array );
  std::cout << "Result: " << result << "\n";
}
  
