#include "Matrix4x4.h"

#include <math.h>
#include <sstream>

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
                                          

Matrix4x4 Matrix4x4::rotationX(int degrees) {
  float radians = (degrees / 180.0f) * M_PI;
  return Matrix4x4::rotationX(radians);
}

Matrix4x4 Matrix4x4::rotationX(float radians) {
  return Matrix4x4(1.0f, 0.0f,            0.0f,             0.0f,
                   0.0f, cosf(radians),   -sinf(radians),   0.0f,
                   0.0f, sinf(radians),   cosf(radians),    0.0f,
                   0.0f, 0.0f,            0.0f,             1.0f);
}

Matrix4x4 Matrix4x4::rotationY(int degrees) {
  float radians = (degrees / 180.0f) * M_PI;
  return Matrix4x4::rotationY(radians);
}

Matrix4x4 Matrix4x4::rotationY(float radians) {
  return Matrix4x4(cosf(radians),     0.0f, sinf(radians),    0.0f,
                   0.0f,              1.0f, 0.0f,             0.0f,
                   -sinf(radians),    0.0f, cosf(radians),    0.0f,
                   0.0f,              0.0f, 0.0f,             1.0f);
}

Matrix4x4 Matrix4x4::rotationZ(int degrees) {
  float radians = (degrees / 180.0f) * M_PI;
  return Matrix4x4::rotationZ(radians);
}

Matrix4x4 Matrix4x4::rotationZ(float radians) {
  return Matrix4x4(cosf(radians), -sinf(radians), 0.0f,   0.0f,
                   sinf(radians), cosf(radians),  0.0f,   0.0f,
                   0.0f,          0.0f,           1.0f,   0.0f,
                   0.0f,          0.0f,           0.0f,   1.0f);
}

Matrix4x4 Matrix4x4::translation(const Vector4& v) {
  return Matrix4x4(1.0f,  0.0f, 0.0f, v.x,
                   0.0f,  1.0f, 0.0f, v.y,
                   0.0f,  0.0f, 1.0f, v.z,
                   0.0f,  0.0f, 0.0f,  1.0f);
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float znear, float zfar) {
  float xymax = znear * tan(fov * (M_PI / 360.0f));
  float ymin = -xymax;
  float xmin = -xymax;
  
  float width = xymax - xmin;
  float height = xymax - ymin;
  
  float depth = zfar - znear;
  float q = -(zfar + znear) / depth;
  float qn = -2 * (zfar * znear) / depth;
  
  float w = 2 * znear / width;
  w = w / aspect;
  float h = 2 * znear / height;
  
  return Matrix4x4(w, 0, 0, 0,
                   0, h, 0, 0, 
                   0, 0, q, -1, 
                   0, 0, qn, 0);
}

Matrix4x4 Matrix4x4::orthographic(float left, float right, float bottom, float top, float near, float far) {
  float w = right / 2.0f;
  float h = top / 2.0f;
  
  float l = -w;
  float r = w;
  float t = h;
  float b = -h;
  
  float n = near;
  float f = far;
  
  return Matrix4x4(
                   2.0f / (r - l) , 0,                 0,               0,
                   0,               2.0f / (t - b) ,   0,               0,
                   0,               0,                -(2.0f / (n - f)),  0,
                   0,               0,                 0,              1);  
}

Matrix4x4::Matrix4x4() {
  
}

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
                     float m21, float m22, float m23, float m24,
                     float m31, float m32, float m33, float m34,
                     float m41, float m42, float m43, float m44)
                    : m11_(m11), m12_(m12), m13_(m13), m14_(m14), 
                      m21_(m21), m22_(m22), m23_(m23), m24_(m24), 
                      m31_(m31), m32_(m32), m33_(m33), m34_(m34),
                      m41_(m41), m42_(m42), m43_(m43), m44_(m44) { }

Vector4 Matrix4x4::operator * (const Vector4& b) const {
  return Vector4(m11_ * b.x + m12_ * b.y + m13_ * b.z + m14_*b.w,
                 m21_ * b.x + m22_ * b.y + m23_ * b.z + m24_*b.w,
                 m31_ * b.x + m32_ * b.y + m33_ * b.z + m34_*b.w,
                 m41_ * b.x + m42_ * b.y + m43_ * b.z + m44_*b.w);
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

Matrix3x3 Matrix4x4::mat3x3() const {
  return Matrix3x3(m11_, m12_, m13_,
                   m21_, m22_, m23_,
                   m31_, m32_, m33_);
}
