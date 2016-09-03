/*
strobogrammatic.cpp: test if a given number looks the same when read upside-down
author: Ulrike Hager
date: July 2016

compile: g++ -Wall -std=c++11 -o strobogrammatic strobogrammatic.cpp
*/


#include <unordered_map>
#include <string>
#include <iostream>


std::unordered_map<char, char> table;


void init_table()
{
  table['0'] = '0';
  table['1'] = '1';
  table['6'] = '9';
  table['9'] = '6';
  table['8'] = '8';
}


void test_number(std::string n_str)
{
  std::string::iterator itb = n_str.begin();
  std::string::iterator ite = n_str.end() - 1;
  while (itb <= ite ) {
    if ( *itb != table[*ite] ) {
      std::cout << n_str << "\033[0;36m is not\033[0;37m a strobogrammatic number.\n" ;
      return;
    }
    ++itb;
    --ite;
  }

  std::cout << n_str << "\033[0;36m is\033[0;37m a strobogrammatic number.\n" ;
}


std::string get_input()
{
  std::string inp;
  std::cout << "Please enter a number: ";
  std::cin >> inp;
  return inp;
}


int main()
{
  init_table();
  std::string input = get_input();

  while ( !input.empty() ){
    test_number( input );
    input = get_input();
  }
}
