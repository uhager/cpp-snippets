#include <iostream>
#include <chrono>
#include <cinttypes>

const int ITERATIONS = 1000000;


uint32_t number_of_digits(uint64_t number)
{
  uint32_t result = 1;
  while (1) {
    if ( number < 10 ) { break; }
    if ( number < 100 ) { result += 1; break; }
    if ( number < 1000 ) { result += 2; break; }
    number /= 1000;
    result += 3;
  }
  //  std::cout << "[number_of_digits] " << result << "\n" ;
  return result;
}


void odd_even_char(uint64_t number)
{
  auto start_time = std::chrono::high_resolution_clock::now();
  bool is_odd = false;
  for (uint32_t i = 0; i < ITERATIONS ; ++i ) {
    uint32_t digits = number_of_digits(number);
    char buffer[digits];
    sprintf(buffer, "%" PRIu64 , number );
    //    std::cout << "last digit: \"" << buffer[digits-1] << "\"\n";
    switch (buffer[digits-1] -'0') {
    case 1: case 3: case 5: case 7: case 9:
      is_odd = true;
      break;
    }
  }
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>> (current_time - start_time).count();
  //std::cout << (is_odd? "odd" : "even") << "\n";
  std::cout << "[odd_even_char] time: " << time << "\n";
}


void odd_even_modulo(uint64_t number)
{
  auto start_time = std::chrono::high_resolution_clock::now();
  bool is_odd = false;
  for (uint32_t i = 0; i < ITERATIONS ; ++i ) {
    asm volatile("");
    if ( number % 2 )
      is_odd = true;
  }
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>> (current_time - start_time).count();
  //std::cout << (is_odd? "odd" : "even") << "\n";
  std::cout << "[odd_even_modulo] time: " << time << "\n";
}


void odd_even_modulo_backwards(uint64_t number)
{
  auto start_time = std::chrono::high_resolution_clock::now();
  bool is_odd = false;
  for (uint32_t i = ITERATIONS; i > 0 ; --i ) {
    if ( number % 2 )
      is_odd = true;
  }
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>> (current_time - start_time).count();
  //std::cout << (is_odd? "odd" : "even") << "\n";
  std::cout << "[odd_even_modulo_backwards] time: " << time << "\n";
}


void odd_even_string(uint64_t number)
{
  auto start_time = std::chrono::high_resolution_clock::now();
  bool is_odd = false;
  for (uint32_t i = 0; i < ITERATIONS ; ++i ) {
    std::string str = std::to_string(number);
    char last = str.at( str.size() - 1 ) - '0';
    switch (last) {
    case 1: case 3: case 5: case 7: case 9:
      is_odd = true;
      break;
    }
  }
  auto current_time = std::chrono::high_resolution_clock::now();
  double time = std::chrono::duration_cast<std::chrono::duration<double>> (current_time - start_time).count();
  //std::cout << (is_odd? "odd" : "even") << "\n";
  std::cout << "[odd_even_string] time: " << time << "\n";
}


int main()
{
  uint64_t number;
  std::cout << "Enter an integer to test: ";
  while (std::cin >> number) {
    odd_even_modulo(number);
    odd_even_string(number);
    odd_even_char(number);
    odd_even_modulo_backwards(number);
    odd_even_modulo(number);
    odd_even_string(number);
    odd_even_char(number);
    odd_even_modulo_backwards(number);
    odd_even_modulo(number);
    odd_even_modulo(number);
    odd_even_string(number);
    odd_even_string(number);
    odd_even_char(number);
    odd_even_char(number);
    odd_even_modulo_backwards(number);
    odd_even_modulo_backwards(number);

    std::cout << "\nEnter a number to test: ";
  }
}
