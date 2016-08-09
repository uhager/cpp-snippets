/*
  HeighwayDragon_strings.cpp: based on https://projecteuler.net/problem=220 but runs out of memory for too many iterations, needs something smarter
  author: Ulrike Hager
  data: Aug. 2016

  compile: g++ -Wall -std=c++11 -o HeighwayDragon_strings HeighwayDragon_strings.cpp
*/

#include <string>
#include <iostream>
#include <vector>
#include <sstream>

std::string next_solution(std::string& current);




struct Point
{
  int x = 0;
  int y = 0;
  int d = 0;  // up = 0, right = 1, down = 2, left = 3
};


std::string find_nth_solution( int n )
{
  std::string input = "Fa";
  for (int i = 0 ; i < n ; ++i ) {
    input = next_solution( input ) ;
  }
  return input;
}


void move_point(Point& p) {
  switch(p.d) {
  case 0: ++p.y; break;
  case 1: ++p.x; break;
  case 2: --p.y; break;
  case 3: --p.x; break;
  }
}


std::string next_solution(std::string& input)
{
  std::string replace_a = "aRbFR";
  std::string replace_b = "LFaLb";
  std::string next;
  for ( auto& c : input ) {
    switch (c) {
    case 'a': next += replace_a; break;
    case 'b': next += replace_b; break;
    default: next += c; break;
    }
  }
  //  std::cout << "next: " << next << "\n";
  return next;
}



Point track_coordinates( const std::string& input, const long& steps )
{
  Point coord;
  long stepped = 0;
  for ( auto& c: input ) {
    switch(c) {
    case 'a' : case 'b' : break;
    case 'L':
      coord.d = ( coord.d + 3 ) % 4 ;
      break;
    case 'R': 
      coord.d = (coord.d + 1) % 4 ;
      break;
    case 'F':
      move_point( coord );
      ++stepped;
      break;
    default: break;
    }
    if ( stepped == steps ) break;
  }
  return coord;
}

// helper function to find pattern in output string
std::string string_to_numbers( const std::string& input )
{
  std::stringstream numbers;
  std::vector<std::string> pattern = {"FaRbFRRL", "FaLbFRRL", "FaRbFRLL", "FaLbFRLL"};
  unsigned int i = 0;
  while ( i < input.size() ) {
    std::string s = input.substr( i, pattern[0].size() );
    for ( unsigned int j = 0; j < pattern.size() ; ++j ) {
      if ( s == pattern[j] ) {
	numbers << j;
	break;
      }
    }
    i += pattern[0].size();
  }

  return numbers.str();
}


  int main()
  {
    int iterations = 8;
    long steps = 111;
    std::string track = find_nth_solution( iterations );
    Point location = track_coordinates( track, steps );
    std::cout << "result D_" << iterations << ": " <<  track << "\nCoordinates after " << steps << " steps: (" << location.x << "," << location.y << ")\n";
    //std::cout << "result D_" << iterations << ": " <<  " Coordinates after " << steps << " steps: (" << location.x << "," << location.y << ")\n";
    //    std::cout << string_to_numbers( track ) << "\n";
  }
