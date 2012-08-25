#include "Vector3.h"

#include "Matrix3x3.h"

#include <math.h>
#include <sstream>

#include "Angles.h"

Vector3 Vector3::IDENTITY = Vector3(0, 0, 0);
Vector3 Vector3::FORWARD = Vector3(0, 0, -1);
Vector3 Vector3::RIGHT = Vector3(1, 0, 0);
Vector3 Vector3::UP = Vector3(0, 1, 0);

Vector3::Vector3(float x_, float y_, float z_) 
  : x(x_), y(y_), z(z_) { }

Vector3::Vector3()
  : x(0), y(0), z(0) { }

Vector3 Vector3::operator + (const Vector3& other) const {
  return Vector3(other.x + x, other.y + y, other.z + z);
}

Vector3 Vector3::operator * (float scalar) const {
  return Vector3(x*scalar, y*scalar, z*scalar);
}

Vector3 Vector3::operator - () const {
  return *this * -1.0f;
}

Vector3 Vector3::rotateX(float radians) {
  Matrix3x3 rotation = Matrix3x3::rotationX(radians);
  return rotation * (*this);
}

Vector3 Vector3::rotateY(float radians) {
  Matrix3x3 rotation = Matrix3x3::rotationY(radians);
  return rotation * (*this);
}

std::string Vector3::toString() const {
  std::stringstream ss;
  ss << x << " " << y << " " << z;
  return ss.str();
}