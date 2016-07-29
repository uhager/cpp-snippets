/*
is_palindrom.cpp checks if the provided input is a palindrom
author: Ulrike Hager
date: July 2016

compile with: g++ -Wall -std=c++11 -o is_palindrome is_palindrome.cpp
 */

#include <string>
#include <vector>
#include <iostream>
#include <sstream>  //istringstream
//#include <algorithm>  // for_each
#include <iterator>

void is_palindrome(std::string& input)
{
  std::cout << "Examining string: \'" << input << "\'\n";
  std::string::iterator in_iter = input.begin();
  std::string::iterator in_riter = input.end()-1;
  for ( ; in_iter != in_riter ; ++in_iter, --in_riter ){
    std::cout << *in_iter << " - " << *in_riter << "\n";
    if ( *in_iter != *in_riter ) {
      std::cout << "\nNot a palindrome!\n" ;
      return;
    }
    
  }
  std::cout << input << " is a palindrome.\n";
}

int main(int argc, char *argv[])
{
  if (argc == 1) { // no input
    std::cout << "Usage:\n is_palindrome a-potential-palindrome\n";
    exit(-1);
  }
  std::vector<std::string> input_vec(argv+1, argv+argc);
  std::string input;
  for (auto const& s: input_vec) input += s;
  //std::for_each(input_vec.begin(), input_vec.end(), [&input](std::string& s){ input += s ;});
  is_palindrome(input);
}
