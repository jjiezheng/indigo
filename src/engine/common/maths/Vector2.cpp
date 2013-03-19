#include "Vector2.h"
#include <sstream>
#include <math.h>

#include "Point.h"

Vector2 Vector2::IDENTITY = Vector2(0, 0);
Vector2 Vector2::UP = Vector2(0, 1);

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

Vector2 Vector2::normalize() const {
	float length = this->length();
	length = length ? length : 1.0f;
	return Vector2(x / length, y / length);
}

void Vector2::normalizeIP() {
	float length = this->length();
	length = length ? length : 1.0f;
	x = x / length;
	y = y / length;
}


float Vector2::angleBetween(const Vector2& other) const {
	float dotProduct = dot(other);

	float aLength = length();
	float bLength = other.length();
	float lengths = aLength * bLength;

	float cosAngle = dotProduct / lengths;
	float angle = acos(cosAngle);
	return angle;
}
