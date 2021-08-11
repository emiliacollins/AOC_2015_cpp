#include <cstdlib>
#include <iostream>
#include <istream>


// Returns net change in Santa's position
short processChar(std::istream& in) {
  char c;

  if (in >> c) {
    switch(c) {
    case ')':
      return -1;
    case '(':
      return 1;
    default:
      throw c;
    }
  }

  return 0;
}


// Calculate Santa's final destination
void part1(std::istream& in) {
  long long accumulator = 0;
  short change = 1;

  // Scan input until EOF is reached
  while (change) {
    try {
      change = processChar(in);
    } catch (char& c) {
      std::cerr << "Invalid character, '" << c << std::endl;
      throw false;
    }

    accumulator += change;
  }

  std::cout << "Santa ends on floor " << accumulator << std::endl;
}


void part2(std::istream& in) {
  long long accumulator = 0;
  size_t index = 0;
  short change = 1;

  // Scan input, stopping on EOF or first instance
  // of negative accumulator
  while (accumulator >= 0 && change) {
    try {
      change = processChar(in);
    } catch (char& c) {
      std::cerr << "Invalid character, '" << c << std::endl;
      throw false;
    }

    accumulator += change;
    index++;
  }

  if (accumulator >= 0) {
    std::cout << "Santa never reached the basement" << std::endl;
  } else {
    std::cout << "Santa reached the basement at position " << index << std::endl;
  }
}


int main() {
  std::istream& inputSource = std::cin;
  try {
    part1(inputSource);
    // part2(inputSource);
  } catch (bool& b) {
    std::cerr << "Error encountered. Exiting..." << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
