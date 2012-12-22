#include "Matrix4x4.h"

#include <sstream>

#include "Trigonometry.h"
#include "Angles.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix3x3.h"

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
    2.0f / (r - l),  0,                 0,                -1,
    0,               2.0f / (t - b) ,   0,                -1,
    0,               0,                -2.0f / (n - f),   0,
    0,               0,                 0,                1);  
}

Matrix4x4::Matrix4x4()
: m11(1.0f), m12(0.0f), m13(0.0f), m14(0.0f), 
  m21(0.0f), m22(1.0f), m23(0.0f), m24(0.0f),
  m31(0.0f), m32(0.0f), m33(1.0f), m34(0.0f),
  m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f) { }

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14,
                     float m21, float m22, float m23, float m24,
                     float m31, float m32, float m33, float m34,
                     float m41, float m42, float m43, float m44)
: m11(m11), m12(m12), m13(m13), m14(m14), 
  m21(m21), m22(m22), m23(m23), m24(m24), 
  m31(m31), m32(m32), m33(m33), m34(m34),
  m41(m41), m42(m42), m43(m43), m44(m44) { }

Matrix4x4::Matrix4x4(const Matrix3x3& m)
: m11(m.m11), m12(m.m12), m13(m.m13), m14(0.0f), 
  m21(m.m21), m22(m.m22), m23(m.m23), m24(0.0f), 
  m31(m.m31), m32(m.m32), m33(m.m33), m34(0.0f),
  m41(0.0f),  m42(0.0f),  m43(0.0f),  m44(1.0f) { }

Matrix4x4::Matrix4x4(const Vector4& m1, const Vector4& m2, const Vector4& m3, const Vector4& m4) 
: m11(m1.x), m12(m2.x), m13(m3.x), m14(m4.x), 
  m21(m1.y), m22(m2.y), m23(m3.y), m24(m4.y), 
  m31(m1.z), m32(m2.z), m33(m3.z), m34(m4.z),
  m41(0.0f), m42(0.0f), m43(0.0f), m44(1.0f) { }


Vector4 Matrix4x4::operator * (const Vector4& b) const {
  return Vector4(m11 * b.x + m12 * b.y + m13 * b.z + m14 * b.w,
    m21 * b.x + m22 * b.y + m23 * b.z + m24 * b.w,
    m31 * b.x + m32 * b.y + m33 * b.z + m34 * b.w,
    m41 * b.x + m42 * b.y + m43 * b.z + m44 * b.w);
}

Matrix4x4 Matrix4x4::operator * (const Matrix4x4& other) const {
  return Matrix4x4(m11 * other.m11 + m12 * other.m21 + m13 * other.m31 + m14 * other.m41,
    m11 * other.m12 + m12 * other.m22 + m13 * other.m32 + m14 * other.m42,
    m11 * other.m13 + m12 * other.m23 + m13 * other.m33 + m14 * other.m43,
    m11 * other.m14 + m12 * other.m24 + m13 * other.m34 + m14 * other.m44,

    m21 * other.m11 + m22 * other.m21 + m23 * other.m31 + m24 * other.m41,
    m21 * other.m12 + m22 * other.m22 + m23 * other.m32 + m24 * other.m42,
    m21 * other.m13 + m22 * other.m23 + m23 * other.m33 + m24 * other.m43,
    m21 * other.m14 + m22 * other.m24 + m23 * other.m34 + m24 * other.m44,

    m31 * other.m11 + m32 * other.m21 + m33 * other.m31 + m34 * other.m41,
    m31 * other.m12 + m32 * other.m22 + m33 * other.m32 + m34 * other.m42,
    m31 * other.m13 + m32 * other.m23 + m33 * other.m33 + m34 * other.m43,
    m31 * other.m14 + m32 * other.m24 + m33 * other.m34 + m34 * other.m44,

    m41 * other.m11 + m42 * other.m21 + m43 * other.m31 + m44 * other.m41,
    m41 * other.m12 + m42 * other.m22 + m43 * other.m32 + m44 * other.m42,
    m41 * other.m13 + m42 * other.m23 + m43 * other.m33 + m44 * other.m43,
    m41 * other.m14 + m42 * other.m24 + m43 * other.m34 + m44 * other.m44);
}

std::string Matrix4x4::toString() const {
  std::stringstream ss;
  ss << m11 << " " << m12 << " " << m13 << " " << m14 << std::endl;
  ss << m21 << " " << m22 << " " << m23 << " " << m24 << std::endl;
  ss << m31 << " " << m32 << " " << m33 << " " << m34 << std::endl;
  ss << m41 << " " << m42 << " " << m43 << " " << m44;
  return ss.str();
}


Matrix4x4 Matrix4x4::inverse() const {
  float subFactor00 = m33 * m44 - m34 * m43;
  float subFactor01 = m23 * m44 - m24 * m43;
  float subFactor02 = m23 * m34 - m24 * m33;
  float subFactor03 = m13 * m44 - m14 * m43;
  float subFactor04 = m13 * m34 - m14 * m33;
  float subFactor05 = m13 * m24 - m14 * m23;
  float subFactor06 = m32 * m44 - m34 * m42;
  float subFactor07 = m22 * m44 - m24 * m42;
  float subFactor08 = m22 * m34 - m24 * m32;
  float subFactor09 = m12 * m44 - m14 * m42;
  float subFactor10 = m12 * m34 - m14 * m32;
  float subFactor11 = m22 * m44 - m24 * m42;
  float subFactor12 = m12 * m24 - m14 * m22;
  float subFactor13 = m32 * m43 - m33 * m42;
  float subFactor14 = m22 * m43 - m23 * m42;
  float subFactor15 = m22 * m33 - m23 * m32;
  float subFactor16 = m12 * m43 - m13 * m42;
  float subFactor17 = m12 * m33 - m13 * m32;
  float subFactor18 = m12 * m23 - m13 * m22;

  Matrix4x4 inverse(
    + m22 * subFactor00 - m32 * subFactor01 + m42 * subFactor02,
    - m12 * subFactor00 + m32 * subFactor03 - m42 * subFactor04,
    + m12 * subFactor01 - m22 * subFactor03 + m42 * subFactor05,
    - m12 * subFactor02 + m22 * subFactor04 - m32 * subFactor05,

    - m21 * subFactor00 + m31 * subFactor01 - m41 * subFactor02,
    + m11 * subFactor00 - m31 * subFactor03 + m41 * subFactor04,
    - m11 * subFactor01 + m21 * subFactor03 - m41 * subFactor05,
    + m11 * subFactor02 - m21 * subFactor04 + m31 * subFactor05,

    + m21 * subFactor06 - m31 * subFactor07 + m41 * subFactor08,
    - m11 * subFactor06 + m31 * subFactor09 - m41 * subFactor10,
    + m11 * subFactor11 - m21 * subFactor09 + m41 * subFactor12,
    - m11 * subFactor08 + m21 * subFactor10 - m31 * subFactor12,

    - m21 * subFactor13 + m31 * subFactor14 - m41 * subFactor15,
    + m11 * subFactor13 - m31 * subFactor16 + m41 * subFactor17,
    - m11 * subFactor14 + m21 * subFactor16 - m41 * subFactor18,
    + m11 * subFactor15 - m21 * subFactor17 + m31 * subFactor18);

  float determinant = 
    + m11 * inverse.m11 
    + m21 * inverse.m12 
    + m31 * inverse.m13 
    + m41 * inverse.m14;

  inverse /= determinant;
  return inverse;
}

Matrix3x3 Matrix4x4::mat3x3() const {
  return Matrix3x3(m11, m12, m13,
    m21, m22, m23,
    m31, m32, m33);
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
    m11 == other.m11 && m12 == other.m12 && m13 == other.m13 && m14 == other.m14 && 
    m21 == other.m21 && m22 == other.m22 && m23 == other.m23 && m24 == other.m24 && 
    m31 == other.m31 && m32 == other.m32 && m33 == other.m33 && m34 == other.m34 && 
    m41 == other.m41 && m42 == other.m42 && m43 == other.m43 && m44 == other.m44;
}

void Matrix4x4::operator /= (float scalar) {
	scalar = (scalar == 0.0f) ? 1.0f : scalar;

	m11 /= scalar;
	m12 /= scalar;
	m13 /= scalar;
	m14 /= scalar;

	m21 /= scalar;
	m22 /= scalar;
	m23 /= scalar;
	m24 /= scalar;

	m31 /= scalar;
	m32 /= scalar;
	m33 /= scalar;
	m34 /= scalar;

	m41 /= scalar;
	m42 /= scalar;
	m43 /= scalar;
	m44 /= scalar;
}