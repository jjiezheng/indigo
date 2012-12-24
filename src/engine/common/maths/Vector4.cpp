#include "Vector4.h"

#include "Matrix4x4.h"
#include "Trigonometry.h"
#include "Vector3.h"

#include <sstream>

#include "Angles.h"

Vector4 Vector4::IDENTITY = Vector4(0, 0, 0, 1);
Vector4 Vector4::FORWARD = Vector4(0, 0, -1, 1);
Vector4 Vector4::RIGHT = Vector4(1, 0, 0, 1);
Vector4 Vector4::UP = Vector4(0, 1, 0, 1);


Vector4::Vector4(float x_, float y_, float z_, float w_) 
  : x(x_), y(y_), z(z_), w(w_) {
  
}

Vector4::Vector4()
  : x(0), y(0), z(0), w(0) {
  
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

Vector4 Vector4::operator - () const {
  return Vector4(-x, -y, -z, -w);
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

void Vector4::operator /= (float scalar) {
  x /= scalar;
  y /= scalar;
  z /= scalar;
  w /= scalar;
}

float Vector4::distance(const Vector4& other) const {
  return (*this - other).length();
}

float Vector4::length() const {
  return sqrt(x * x + y * y + z * z);
}

Vector4 Vector4::rotateX(float degrees) {
  Matrix4x4 rotation = Matrix4x4::rotationX(toRadians(degrees));
  return rotation * *this;
}

Vector4 Vector4::rotateY(float degrees) {
  Matrix4x4 rotation = Matrix4x4::rotationY(toRadians(degrees));
  return rotation * *this;
}

std::string Vector4::toString() const {
  std::stringstream ss;
  ss << "{" << x << ", " << y << ", " << z << ", " << w << "}";
  return ss.str();
}

Vector4 Vector4::cross(const Vector4& other) const {
  return Vector4(
    y * other.z - z * other.y,
    z * other.x - x * other.z,
    x * other.y - y * other.x,
    0.0f);
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
  length = length ? length : 1.0f;
  return Vector4(x / length, y / length, z / length, 1.0f);
}

Vector4 Vector4::inverse() const {
  return Vector4(-x, -y, -z, -w);
}