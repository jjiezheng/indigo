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

Vector4 Vector4::operator - (const Vector4& other) const {
  return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
}

Vector4 Vector4::operator-() const {
  return Vector4(-x, -y, -z);
}

Vector4 Vector4::operator * (float scalar) const {
  return Vector4(x*scalar, y*scalar, z*scalar, w*scalar);
}

bool Vector4::operator == (const Vector4& other) const {
  return other.x == x && other.y == y && other.z == z && other.w == w;
}

bool Vector4::operator != (const Vector4& other) const {
  return !(*this == other);
}


float Vector4::distance(const Vector4& other) const {
  return (*this - other).length();
}

float Vector4::length() const {
  return sqrt(x * x + y * y + z * z);
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

Vector4 Vector4::cross(const Vector4& other) const {
  return Vector4(
    y * other.z - z * other.y,
    z * other.x - x * other.z,
    x * other.y - y * other.x);
}

float Vector4::dot( const Vector4& other ) const {
  return x * other.x + y * other.y + z * other.z;
}

float Vector4::angle(const Vector4& other) const {
  float dotResult = this->dot(other);
  return acos(dotResult);
}

Vector3 Vector4::vec3() const {
  return Vector3(x, y, z);
}

Vector4 Vector4::normalize() const {
  float length = this->length();
  return Vector4(x / length, y / length, z / length, w / length);
}
