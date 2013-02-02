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

Vector3 Vector3::operator - (const Vector3& other) const {
  return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator * (float scalar) const {
  return Vector3(x*scalar, y*scalar, z*scalar);
}

Vector3 Vector3::operator - () const {
  return *this * -1.0f;
}

Vector3 Vector3::operator * (const Vector3& other) const {
	return Vector3(
		x * other.x,
		y * other.y,
		z * other.z);
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

Vector3 Vector3::cross(const Vector3& other) const {
  return Vector3(
    y * other.z - z * other.y,
    z * other.x - x * other.z,
    x * other.y - y * other.x);
}

Vector3 Vector3::normalize() const {
  float length = this->length();
  length = length ? length : 1.0f;
  return Vector3(x / length, y / length, z / length);
}

float Vector3::length() const {
  return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::inverse() const {
  return -(*this);
}

float Vector3::dot(const Vector3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

void Vector3::normalizeIP() {
	float length = this->length();
	length = length ? length : 1.0f;
	x = x / length;
	y = y / length;
	z = z / length;
}

float Vector3::angleBetween(const Vector3& other) const {
	float dotProduct = dot(other);

	float aLength = length();
	float bLength = other.length();
	float lengths = aLength * bLength;

	if (lengths == 0) {
		return 0;
	}

	lengths = lengths ? lengths : 1.0f;

	float cosAngle = dotProduct / lengths;
	float angle = acos(cosAngle);
	return angle;
}

float Vector3::distance(const Vector3& other) const {
  return (*this - other).length();
}
