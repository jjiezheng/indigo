#include "Vector4.h"

#include "Matrix4x4.h"

#include "Vector3.h"

#include <math.h>
#include <sstream>

Vector4 Vector4::IDENTITY = Vector4(0, 0, 0, 1);
Vector4 Vector4::FORWARD = Vector4(0, 0, -1, 1);
Vector4 Vector4::RIGHT = Vector4(1, 0, 0, 1);
Vector4 Vector4::UP = Vector4(0, 1, 0, 1);

Vector4::Vector4(float x_, float y_, float z_) 
  : x(x_), y(y_), z(z_), w(1) {
  
}


Vector4::Vector4(float x_, float y_, float z_, float w_) 
  : x(x_), y(y_), z(z_), w(w_) {
  
}

Vector4::Vector4()
  : x(0), y(0), z(0), w(1) {
  
}

Vector4::Vector4(const Vector3& v)
  : x(v.x), y(v.y), z(v.z), w(1) { 
  
}

Vector4 Vector4::operator + (const Vector4& other) const {
  return Vector4(other.x + x, other.y + y, other.z + z, other.w + w);
}

Vector4 Vector4::operator * (float scalar) const {
  return Vector4(x*scalar, y*scalar, z*scalar, w*scalar);
}

Vector4 Vector4::operator == (const Vector4& other) const {
  return Vector4(other.x == x, other.y == y, other.z == z, other.w == w);
}

Vector4 Vector4::rotateX(int degrees) {
  Matrix4x4 rotation = Matrix4x4::rotationX(degrees);
  return rotation * *this;
}

Vector4 Vector4::rotateY(int degrees) {
  Matrix4x4 rotation = Matrix4x4::rotationY(degrees);
  return rotation * *this;
}

std::string Vector4::toString() const {
  std::stringstream ss;
  ss << x << " " << y << " " << z << " " << w;
  return ss.str();
}