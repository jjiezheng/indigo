#include "Matrix4x4.h"

#include <sstream>

#include "Trigonometry.h"
#include "Angles.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"

#include "glm/glm.hpp"
#include "glm/gtx/projection.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

Matrix4x4 Matrix4x4::IDENTITY = Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
                                          0.0f, 1.0f, 0.0f, 0.0f,
                                          0.0f, 0.0f, 1.0f, 0.0f,
                                          0.0f, 0.0f, 0.0f, 1.0f);

Matrix4x4 Matrix4x4::rotation(const Vector4& axis, float angleRadians) {
  return Matrix4x4(Matrix3x3::rotation(axis.vec3(), angleRadians));
}

Matrix4x4 Matrix4x4::rotationX(float radians) {
  return Matrix4x4(Matrix3x3::rotationX(radians));
}

Matrix4x4 Matrix4x4::rotationY(float radians) {
  return Matrix4x4(Matrix3x3::rotationY(radians));
}

Matrix4x4 Matrix4x4::rotationZ(float radians) {
  return Matrix4x4(Matrix3x3::rotationZ(radians));
}

Matrix4x4 Matrix4x4::translation(const Vector4& v) {
  return Matrix4x4(1.0f,  0.0f, 0.0f, v.x,
    0.0f,  1.0f, 0.0f, v.y,
    0.0f,  0.0f, 1.0f, v.z,
    0.0f,  0.0f, 0.0f, 1.0f);
}

Matrix4x4 Matrix4x4::scale(float scale) {
  return Matrix4x4::scale(Vector4(scale, scale, scale, 1.0f));
}

Matrix4x4 Matrix4x4::scale(const Vector4& v) {
  return Matrix4x4(Matrix3x3::scale(v.vec3()));
}

// x: -1 to 1, y: -1 to 1, z: 0 to 1
Matrix4x4 Matrix4x4::perspective(float fovDegrees, float aspect, float zNear, float zFar) {
  float fovY = toRadians(fovDegrees);

  float f = 1.0f / tanf(0.5f * fovY);
  float e = (zNear - zFar);

  float a = zFar / e;
  float b = (zFar * zNear) / e;

  Matrix4x4 result = Matrix4x4(
   f/aspect,  0,       0,       0,
    0,        f,       0,       0,
    0,        0,       a,      -1,
    0,        0,       b,       0);

  return result;
}

// x: -1 to 1, y: -1 to 1, z: -1 to 1
// Matrix4x4 Matrix4x4::perspective(float fovDegrees, float aspect, float zNear, float zFar) {
//   float fovY = toRadians(fovDegrees);
// 
//   float f = 1.0f / tanf(0.5f * fovY);
//   float e = (zNear - zFar);
//   
//   float a = (zFar + zNear) / e;
//   float b = (2.0f * zFar * zNear) / e;
// 
//   Matrix4x4 result = Matrix4x4(
//     f/aspect, 0,       0,       0,
//     0,        f,       0,       0,
//     0,        0,       a,       b,
//     0,        0,       -1,      0);
// 
//   return result;
// }

Matrix4x4 Matrix4x4::orthographic(float left, float right, float bottom, float top, float znear, float zfar) {
  float w = right / 2.0f;
  float h = top / 2.0f;

  float l = -w;
  float r = w;
  float t = h;
  float b = -h;

  float n = znear;
  float f = zfar;

  return Matrix4x4(
    2.0f / (r - l) , 0,                 0,                0,
    0,               2.0f / (t - b) ,   0,                0,
    0,               0,                -(2.0f / (n - f)), 0,
    0,               0,                 0,                1);  
}

Matrix4x4::Matrix4x4()
: m11_(1.0f), m12_(0.0f), m13_(0.0f), m14_(0.0f), 
  m21_(0.0f), m22_(1.0f), m23_(0.0f), m24_(0.0f),
  m31_(0.0f), m32_(0.0f), m33_(1.0f), m34_(0.0f),
  m41_(0.0f), m42_(0.0f), m43_(0.0f), m44_(1.0f) { }

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
                     float m21, float m22, float m23, float m24,
                     float m31, float m32, float m33, float m34,
                     float m41, float m42, float m43, float m44)
: m11_(m11), m12_(m12), m13_(m13), m14_(m14), 
  m21_(m21), m22_(m22), m23_(m23), m24_(m24), 
  m31_(m31), m32_(m32), m33_(m33), m34_(m34),
  m41_(m41), m42_(m42), m43_(m43), m44_(m44) { }

Matrix4x4::Matrix4x4(const Matrix3x3& m)
: m11_(m.m11), m12_(m.m12), m13_(m.m13), m14_(0.0f), 
  m21_(m.m21), m22_(m.m22), m23_(m.m23), m24_(0.0f), 
  m31_(m.m31), m32_(m.m32), m33_(m.m33), m34_(0.0f),
  m41_(0.0f),  m42_(0.0f),  m43_(0.0f),  m44_(1.0f) { }

Matrix4x4::Matrix4x4(const Vector4& m1, const Vector4& m2, const Vector4& m3, const Vector4& m4) 
: m11_(m1.x), m12_(m2.x), m13_(m3.x), m14_(m4.x), 
  m21_(m1.y), m22_(m2.y), m23_(m3.y), m24_(m4.y), 
  m31_(m1.z), m32_(m2.z), m33_(m3.z), m34_(m4.z),
  m41_(0.0f), m42_(0.0f), m43_(0.0f), m44_(1.0f) { }


Vector4 Matrix4x4::operator * (const Vector4& b) const {
  return Vector4(m11_ * b.x + m12_ * b.y + m13_ * b.z + m14_ * b.w,
    m21_ * b.x + m22_ * b.y + m23_ * b.z + m24_ * b.w,
    m31_ * b.x + m32_ * b.y + m33_ * b.z + m34_ * b.w,
    m41_ * b.x + m42_ * b.y + m43_ * b.z + m44_ * b.w);
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& other) const {
  return Matrix4x4(m11_ * other.m11_ + m12_ * other.m21_ + m13_ * other.m31_ + m14_ * other.m41_,
    m11_ * other.m12_ + m12_ * other.m22_ + m13_ * other.m32_ + m14_ * other.m42_,
    m11_ * other.m13_ + m12_ * other.m23_ + m13_ * other.m33_ + m14_ * other.m43_,
    m11_ * other.m14_ + m12_ * other.m24_ + m13_ * other.m34_ + m14_ * other.m44_,

    m21_ * other.m11_ + m22_ * other.m21_ + m23_ * other.m31_ + m24_ * other.m41_,
    m21_ * other.m12_ + m22_ * other.m22_ + m23_ * other.m32_ + m24_ * other.m42_,
    m21_ * other.m13_ + m22_ * other.m23_ + m23_ * other.m33_ + m24_ * other.m43_,
    m21_ * other.m14_ + m22_ * other.m24_ + m23_ * other.m34_ + m24_ * other.m44_,

    m31_ * other.m11_ + m32_ * other.m21_ + m33_ * other.m31_ + m34_ * other.m41_,
    m31_ * other.m12_ + m32_ * other.m22_ + m33_ * other.m32_ + m34_ * other.m42_,
    m31_ * other.m13_ + m32_ * other.m23_ + m33_ * other.m33_ + m34_ * other.m43_,
    m31_ * other.m14_ + m32_ * other.m24_ + m33_ * other.m34_ + m34_ * other.m44_,

    m41_ * other.m11_ + m42_ * other.m21_ + m43_ * other.m31_ + m44_ * other.m41_,
    m41_ * other.m12_ + m42_ * other.m22_ + m43_ * other.m32_ + m44_ * other.m42_,
    m41_ * other.m13_ + m42_ * other.m23_ + m43_ * other.m33_ + m44_ * other.m43_,
    m41_ * other.m14_ + m42_ * other.m24_ + m43_ * other.m34_ + m44_ * other.m44_);
}

std::string Matrix4x4::toString() const {
  std::stringstream ss;
  ss << m11_ << " " << m12_ << " " << m13_ << " " << m14_ << std::endl;
  ss << m21_ << " " << m22_ << " " << m23_ << " " << m24_ << std::endl;
  ss << m31_ << " " << m32_ << " " << m33_ << " " << m34_ << std::endl;
  ss << m41_ << " " << m42_ << " " << m43_ << " " << m44_;
  return ss.str();
}

Matrix4x4 Matrix4x4::inverse() const {
  glm::mat4 mat(m11_, m12_, m13_, m14_,
    m21_, m22_, m23_, m24_,
    m31_, m32_, m33_, m34_,
    m41_, m42_, m43_, m44_);
  glm::mat4 inv = glm::inverse(mat);
  return Matrix4x4(inv[0][0], inv[0][1], inv[0][2], inv[0][3],
    inv[1][0], inv[1][1], inv[1][2], inv[1][3],
    inv[2][0], inv[2][1], inv[2][2], inv[2][3],
    inv[3][0], inv[3][1], inv[3][2], inv[3][3]);
}

Matrix4x4 Matrix4x4::transpose() const {
  glm::mat4 mat(m11_, m12_, m13_, m14_,
    m21_, m22_, m23_, m24_,
    m31_, m32_, m33_, m34_,
    m41_, m42_, m43_, m44_);
  glm::mat4 inv = glm::transpose(mat);
  return Matrix4x4(inv[0][0], inv[0][1], inv[0][2], inv[0][3],
    inv[1][0], inv[1][1], inv[1][2], inv[1][3],
    inv[2][0], inv[2][1], inv[2][2], inv[2][3],
    inv[3][0], inv[3][1], inv[3][2], inv[3][3]);
}

Matrix3x3 Matrix4x4::mat3x3() const {
  return Matrix3x3(m11_, m12_, m13_,
    m21_, m22_, m23_,
    m31_, m32_, m33_);
}

Matrix4x4 Matrix4x4::lookAt(const Vector4& eye, const Vector4& target, const Vector4& worldUp) {
  Vector4 forward = eye - target;
  Vector4 forwardN = forward.normalize();

  Vector4 worldUpN = worldUp.normalize();

  Vector4 right = worldUpN.cross(forwardN);
  Vector4 rightN = right.normalize();

  Vector4 up = forwardN.cross(rightN);
  Vector4 upN = up.normalize();

  float x = -right.dot(eye);
  float y = -up.dot(eye);
  float z = -forward.dot(eye);

  Matrix4x4 lookAt(
    rightN.x,   rightN.y,       rightN.z,     x,
    upN.x,      upN.y,          upN.z,        y,
    forwardN.x, forwardN.y,     forwardN.z,   z,
    0.0f,       0.0f,           0.0f,         1.0f);

  return lookAt;
}

bool Matrix4x4::operator==(const Matrix4x4& other) const {
  return 
    m11_ == other.m11_ && m12_ == other.m12_ && m13_ == other.m13_ && m14_ == other.m14_ && 
    m21_ == other.m21_ && m22_ == other.m22_ && m23_ == other.m23_ && m24_ == other.m24_ && 
    m31_ == other.m31_ && m32_ == other.m32_ && m33_ == other.m33_ && m34_ == other.m34_ && 
    m41_ == other.m41_ && m42_ == other.m42_ && m43_ == other.m43_ && m44_ == other.m44_;
}

void Matrix4x4::operator /= (float scalar) {
	scalar = (scalar == 0.0f) ? 1.0f : scalar;

	m11_ /= scalar;
	m12_ /= scalar;
	m13_ /= scalar;
	m14_ /= scalar;

	m21_ /= scalar;
	m22_ /= scalar;
	m23_ /= scalar;
	m24_ /= scalar;

	m31_ /= scalar;
	m32_ /= scalar;
	m33_ /= scalar;
	m34_ /= scalar;

	m41_ /= scalar;
	m42_ /= scalar;
	m43_ /= scalar;
	m44_ /= scalar;
}