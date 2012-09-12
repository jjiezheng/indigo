#include "Matrix4x4.h"

#include <sstream>
#include <assert.h>

#include "Trigonometry.h"
#include "Angles.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"

#include "platform/PlatformDefs.h"

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

Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float znear, float zfar) {
  float range = tan(fov / 2.0f) * znear;	
  float left = -range * aspect;
  float right = range * aspect;
  float bottom = -range;
  float top = range;

  return Matrix4x4(
    (2.0f * znear) / (right - left),      0.0f,                                     0.0f,                               0.0f,
    0.0f,                                 (2.0f * znear) / (top - bottom),          0.0f,                               0.0f,
    0.0f,                                 0.0f,                                     -(zfar + znear) / (zfar - znear),   -(2.0f * zfar * znear) / (zfar - znear),
    0.0f,                                 0.0f,                                     -1.0f,                              1.0f);
}

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

std::string Matrix4x4::toString() const {
  std::stringstream ss;
  ss << m11_ << " " << m12_ << " " << m13_ << " " << m14_ << std::endl;
  ss << m21_ << " " << m22_ << " " << m23_ << " " << m24_ << std::endl;
  ss << m31_ << " " << m32_ << " " << m33_ << " " << m34_ << std::endl;
  ss << m41_ << " " << m42_ << " " << m43_ << " " << m44_;
  return ss.str();
}

Matrix4x4 Matrix4x4::inverse() const {
  float subFactor00 = m33_ * m44_ - m34_ * m43_;
  float subFactor01 = m23_ * m44_ - m24_ * m43_;
  float subFactor02 = m23_ * m34_ - m24_ * m33_;
  float subFactor03 = m13_ * m44_ - m14_ * m43_;
  float subFactor04 = m13_ * m34_ - m14_ * m33_;
  float subFactor05 = m13_ * m24_ - m14_ * m23_;
  float subFactor06 = m32_ * m44_ - m34_ * m42_;
  float subFactor07 = m22_ * m44_ - m24_ * m42_;
  float subFactor08 = m22_ * m34_ - m24_ * m32_;
  float subFactor09 = m12_ * m44_ - m14_ * m42_;
  float subFactor10 = m12_ * m34_ - m14_ * m32_;
  float subFactor11 = m22_ * m44_ - m24_ * m42_;
  float subFactor12 = m12_ * m24_ - m14_ * m22_;
  float subFactor13 = m32_ * m43_ - m33_ * m42_;
  float subFactor14 = m22_ * m43_ - m23_ * m42_;
  float subFactor15 = m22_ * m33_ - m23_ * m32_;
  float subFactor16 = m12_ * m43_ - m13_ * m42_;
  float subFactor17 = m12_ * m33_ - m13_ * m32_;
  float subFactor18 = m12_ * m23_ - m13_ * m22_;

  Matrix4x4 inverse(
    + m22_ * subFactor00 - m32_ * subFactor01 + m42_ * subFactor02,
    - m12_ * subFactor00 + m32_ * subFactor03 - m42_ * subFactor04,
    + m12_ * subFactor01 - m22_ * subFactor03 + m42_ * subFactor05,
    - m12_ * subFactor02 + m22_ * subFactor04 - m32_ * subFactor05,

    - m21_ * subFactor00 + m31_ * subFactor01 - m41_ * subFactor02,
    + m11_ * subFactor00 - m31_ * subFactor03 + m41_ * subFactor04,
    - m11_ * subFactor01 + m21_ * subFactor03 - m41_ * subFactor05,
    + m11_ * subFactor02 - m21_ * subFactor04 + m31_ * subFactor05,

    + m21_ * subFactor06 - m31_ * subFactor07 + m41_ * subFactor08,
    - m11_ * subFactor06 + m31_ * subFactor09 - m41_ * subFactor10,
    + m11_ * subFactor11 - m21_ * subFactor09 + m41_ * subFactor12,
    - m11_ * subFactor08 + m21_ * subFactor10 - m31_ * subFactor12,

    - m21_ * subFactor13 + m31_ * subFactor14 - m41_ * subFactor15,
    + m11_ * subFactor13 - m31_ * subFactor16 + m41_ * subFactor17,
    - m11_ * subFactor14 + m21_ * subFactor16 - m41_ * subFactor18,
    + m11_ * subFactor15 - m21_ * subFactor17 + m31_ * subFactor18);

  float determinant = 
    + m11_ * inverse.m11_ 
    + m21_ * inverse.m12_ 
    + m31_ * inverse.m13_ 
    + m41_ * inverse.m14_;

  inverse /= determinant;
  return inverse;
}

Matrix3x3 Matrix4x4::mat3x3() const {
  return Matrix3x3(m11_, m12_, m13_,
                   m21_, m22_, m23_,
                   m31_, m32_, m33_);
}

Matrix4x4 Matrix4x4::lookAt(const Vector4& eye, const Vector4& target, const Vector4& worldUp) {
  Vector4 eyeN = eye.normalize();

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
