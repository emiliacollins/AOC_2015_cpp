#include <iostream>
#include <istream>
#include <ios>
#include <unordered_set>
#include <functional>


class Vector {
  friend std::istream& operator>>(std::istream& in, Vector& val);
public:
  Vector() {}
  Vector(short dx, short dy) :
    dx(dx), dy(dy) {}
  short getdx() const {
    return dx;
  }
  short getdy() const {
    return dy;
  }
private:
  short dx;
  short dy;
};

std::istream& operator>>(std::istream& in, Vector& val) {
  char c;
  if (! (in >> c)) {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  switch(c) {
  case '^':
    val.dx = -1;
    val.dy = 0;
    break;
  case'v':
    val.dx = 1;
    val.dy = 0;
    break;
  case '<':
    val.dx = 0;
    val.dy = -1;
    break;
  case '>':
    val.dx = 0;
    val.dy = 1;
    break;
  default:
    in.setstate(std::ios::failbit);
  }

  return in;
}


struct Coord {
  long long x;
  long long y;

  bool operator==(const Coord& other) const {
    return other.x == x && other.y == y; 
  }

  void applyVector(const Vector& vec) {
    x += vec.getdx();
    y += vec.getdy();
  }
};

namespace std {
  template<>
  struct hash<Coord> {
    size_t operator()(const Coord& c) const {
      return
	(std::hash<long long>()(c.x) << 8)
	^ (~std::hash<long long>()(c.y));
    }
  };
}


void part1(std::istream& in) {
  Vector vec(0, 0);
  Coord position { 0, 0 };
  std::unordered_set<Coord> visited;

  do {
    position.applyVector(vec);
    visited.insert(position);
  } while (in >> vec);

  std::cout << visited.size() << " houses receive at least one present." << std::endl;
}

void part2(std::istream& in) {
  Vector vec(0, 0);
  Coord santaPos { 0, 0 };
  Coord roboPos { 0, 0};
  std::unordered_set<Coord> visited;

  do {
    roboPos.applyVector(vec);
    visited.insert(roboPos);
    if (in >> vec) {
      santaPos.applyVector(vec);
      visited.insert(santaPos);
    }
  } while (in >> vec);

  std::cout << visited.size() << " houses receive at least one present." << std::endl;
  
}

int main() {
  std::istream& inputSource = std::cin;

  part1(inputSource);
  //part2(inputSource);

  return EXIT_SUCCESS;
}
