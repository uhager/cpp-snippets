/* look_and_say.cpp: generates look-and-say sequence up to given number. 
author: Ulrike Hager
data: Feb. 2016
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <cstdio>


void
print_solution_ostream(const std::vector<char>& solution, unsigned int pos)
{
  if ( pos > solution.size() ) {
    std::cerr << "[print_solution] Error: trying to print out of range" << std::endl;
    return;
  }
  std::ostream_iterator<char> iter(std::cout);
  std::copy(solution.begin(), solution.begin()+pos, iter);
  std::cout << "\n"; 
}


void
print_solution_printf(const std::vector<char>& solution, unsigned int pos)
{
  if ( pos > solution.size() ) {
    std::cerr << "[print_solution] Error: trying to print out of range" << std::endl;
    return;
  }
  std::for_each(solution.begin(), solution.begin()+pos, 
		[] (char c) { std::printf("%c", c) ;} );
  std::printf("\n");
}



void
append_char(std::vector<char>& solution, unsigned int& pos, char to_add)
{
  if ( pos < solution.size() )
    solution.at(pos) = to_add;
  else
    solution.push_back( to_add );
  ++pos;

}

void
append_solution(std::vector<char>& solution, unsigned int& pos, int count, char digit)
{
  append_char( solution, pos, (char)( count )+ '0' );
  append_char( solution, pos, digit );	       
}


void
swap_solutions(std::vector<char>& curr_sol, unsigned int& curr_pos, std::vector<char>& next_sol, unsigned int &next_pos)
{
  std::swap(curr_sol, next_sol);
  curr_pos = next_pos;
  next_pos = 0;
}


void
next_solution(std::vector<char>& curr_sol, unsigned int& curr_pos, std::vector<char>& next_sol, unsigned int &next_pos)
{
  int count = 1;
  for (unsigned int i = 0; i < curr_pos; ++i ) {
    if ( i < curr_pos -1 ) {
      if ( curr_sol.at(i) == curr_sol.at(i+1) ) {
	count++;
      }
      else {
	append_solution(next_sol, next_pos, count, curr_sol.at(i));
	count = 1;
      }
    }
    else {
      append_solution(next_sol, next_pos, count, curr_sol.at(i));
    }
  }
  swap_solutions(curr_sol, curr_pos, next_sol, next_pos);
}


double
calculate_solutions_printf(unsigned int num, std::string ini)
{

  auto start_time = std::chrono::high_resolution_clock::now();
  
  unsigned int curr_pos = ini.size(), next_pos = 0;
  std::vector<char> curr_sol(1000), next_sol(1000);
  std::copy( ini.begin(), ini.end(), curr_sol.begin() );

 for (unsigned int i = 0; i < num-1; ++i ) {
    print_solution_printf(curr_sol, curr_pos);
    next_solution(curr_sol, curr_pos, next_sol, next_pos);
  }
  print_solution_printf(curr_sol, curr_pos);
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time).count();
  std::cout << "Time to calculate + printf: " << std::to_string(time) << "\n";
  return time;
}


double
calculate_solutions_ostream(unsigned int num, std::string ini)
{

  auto start_time = std::chrono::high_resolution_clock::now();
  
  unsigned int curr_pos = ini.size(), next_pos = 0;
  std::vector<char> curr_sol(1000), next_sol(1000);
  std::copy( ini.begin(), ini.end(), curr_sol.begin() );

 for (unsigned int i = 0; i < num-1; ++i ) {
    print_solution_ostream(curr_sol, curr_pos);
    next_solution(curr_sol, curr_pos, next_sol, next_pos);
  }
  print_solution_ostream(curr_sol, curr_pos);
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - start_time).count();
  std::cout << "Time to calculate + ostream: " << std::to_string(time) << "\n";
  return time;
}


std::string
read_starting_sequence()
{
  std::string ini = "1";
  std::cout << "Enter the starting sequence (integer): " ;
  std::cin >> ini;
  return ini;
}

int main()
{
  unsigned int num = 0;
  std::cout << "Enter the number of sequences to calculate: ";
  
  while (std::cin >> num ){
    std::string ini_sol = read_starting_sequence();
    double time1 = calculate_solutions_ostream(num, ini_sol);
    double time2 = calculate_solutions_ostream(num, ini_sol);
    double time3 = calculate_solutions_printf(num, ini_sol);
    double time4 = calculate_solutions_printf(num, ini_sol);
    double time5 = calculate_solutions_ostream(num, ini_sol);
    std::cout << "times: \n"
	      << "ostream: " << time1 << ", " << time2 << "\n"
	      << "printf: "  << time3 << ", " << time4 << "\n" 
	      << "ostream: " << time5 << "\n";
    std::cout << "\nEnter the number of sequences to calculate: " ;
  }
}

