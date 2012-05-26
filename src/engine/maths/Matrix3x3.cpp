#include "Matrix3x3.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Vector3.h"

Matrix3x3 Matrix3x3::rotationX(int degrees) {
  float angleRads = (degrees / 180.0f) * (float)M_PI;
  return Matrix3x3(1.0f, 0.0f,             0.0f, 
                   0.0f, cosf(angleRads), -sinf(angleRads),
                   0.0f, sinf(angleRads),  cosf(angleRads));
}

Matrix3x3 Matrix3x3::rotationX(float radians) {
  return Matrix3x3(1.0f, 0.0f,           0.0f, 
                   0.0f, cosf(radians), -sinf(radians),
                   0.0f, sinf(radians),  cosf(radians));
}

Matrix3x3 Matrix3x3::rotationY(int degrees) {
  float angleRads = (degrees / 180.0f) *(float) M_PI;
  return Matrix3x3(cosf(angleRads),   0.0f, sinf(angleRads), 
                   0.0f,              1.0f, 0.0f,
                   -sinf(angleRads),  0.0f, cosf(angleRads));
}

Matrix3x3 Matrix3x3::rotationY(float radians) {
  return Matrix3x3(cosf(radians),   0.0f, sinf(radians), 
                   0.0f,            1.0f, 0.0f,
                   -sinf(radians),  0.0f, cosf(radians));
}

Matrix3x3::Matrix3x3()
  : m11_(1.0f), m12_(0.0f), m13_(0.0f), 
    m21_(0.0f), m22_(1.0f), m23_(0.0f), 
    m31_(0.0f), m32_(0.0f), m33_(1.0f) { }

Matrix3x3::Matrix3x3(float m11, float m12, float m13,
                     float m21, float m22, float m23,
                     float m31, float m32, float m33)
  : m11_(m11), m12_(m12), m13_(m13), 
    m21_(m21), m22_(m22), m23_(m23), 
    m31_(m31), m32_(m32), m33_(m33) { }

Vector3 Matrix3x3::operator * (const Vector3& b) const {
  return Vector3(m11_ * b.x + m12_ * b.y + m13_ * b.z,
                 m21_ * b.x + m22_ * b.y + m23_ * b.z,
                 m31_ * b.x + m32_ * b.y + m33_ * b.z);
}