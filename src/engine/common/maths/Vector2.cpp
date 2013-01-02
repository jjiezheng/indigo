#include "Vector2.h"
#include <sstream>

#include "Point.h"

Vector2 Vector2::IDENTITY = Vector2(0, 0);

Vector2::Vector2() 
  : x(0), y(0) { }

Vector2::Vector2(const Point& p) 
  : x(float(p.x)), y(float(p.y)) { }

Vector2::Vector2(float x_, float y_) 
  : x(x_), y(y_) { }

std::string Vector2::toString() const {
  std::stringstream ss;
  ss << x << " " << y;
  return ss.str();
}