#include <cstdlib>
#include <ios>
#include <iostream>
#include <istream>


class SideDimensions {
public:
  SideDimensions() {}
  SideDimensions(size_t x, size_t y) :
    x(x), y(y) {}

  size_t perimeter() const {
    return 2 * (x + y);
  }

  size_t surfaceArea() const {
    return x * y;
  }
  
private:
  size_t x;
  size_t y;
};


class BoxDimensions {
  friend std::istream& operator>> (std::istream& in, BoxDimensions& val);
public:
  BoxDimensions() {}
  BoxDimensions(size_t x, size_t y, size_t z) :
    x(x), y(y), z(z) {}
  
  size_t surfaceArea() const {
    return 2 * (x * (y + z) + y * z);
  }

  size_t volume() const {
    return x * y * z;
  }
  
  SideDimensions smallestSide() const {
    if (x < y) {
      if (y < z) {
	// x < y < z
	return SideDimensions(x, y);
      } else {
	// x < y, z <= y
	return SideDimensions(x, z);
      }
    } else if (x < z) {
      // x >= y, x < z
      return SideDimensions(y, x);
    }
    // x >= y, x >= z
    return SideDimensions(y, z);
  }
  
private:
  size_t x;
  size_t y;
  size_t z;
};


std::istream& operator>> (std::istream& in, BoxDimensions& val) {
  char x = ' ';
  if (in >> val.x
      && in >> x
      && x == 'x'
      && in >> val.y
      && in >> x
      && x == 'x'
      && in >> val.z)
    {
      return in;
    }

  in.setstate(std::ios::failbit);
  return in;
}


void part1(std::istream& in) {
  BoxDimensions d;
  size_t totalReqSA = 0;
  while (in >> d) {
    totalReqSA += d.surfaceArea() + d.smallestSide().surfaceArea();
  }

  std::cout << totalReqSA << " sqft of wrapping paper required." << std::endl;
}


void part2(std::istream& in) {
  BoxDimensions d;
  size_t totalReqLength = 0;

  while (in >> d) {
    totalReqLength += d.smallestSide().perimeter() + d.volume();
  }

  std::cout << totalReqLength << " feet of ribbon required." << std::endl;
}


int main() {
  std::istream& inputSource = std::cin;

  try {
    part1(inputSource);
    //part2(inputSource);
  } catch(bool& b) {
    std::cerr << "Error encountered. Exiting..." << std::endl;
    return EXIT_FAILURE;
  }
  
  return EXIT_SUCCESS;
}
