#ifndef MATRIX4x4_H
#define MATRIX4x4_H

#include <string>

class Vector4;
class Vector3;
class Matrix3x3;

class Matrix4x4 {
  
public:

  static Matrix4x4 rotation(const Vector4& axis, float angleRadians);
  
  static Matrix4x4 rotationX(float radians);
    
  static Matrix4x4 rotationY(float radians);
  
  static Matrix4x4 rotationZ(float radians);  

public:
  
  static Matrix4x4 translation(const Vector4& v);
  
  static Matrix4x4 scale(const Vector4& v);
  
  static Matrix4x4 scale(float scale);
  
public:

  static Matrix4x4 lookAt(const Vector4& eye, const Vector4& target, const Vector4& up);

  static Matrix4x4 perspective(float fovDegrees, float aspect, float znear, float zfar);
  
  static Matrix4x4 orthographic(float left, float right, float bottom, float top, float near, float far);
  
public:
  
  std::string toString() const;
  
  Matrix4x4 inverse() const;

  Matrix3x3 mat3x3() const;
  
public:
  
  Matrix4x4();

  Matrix4x4(const Vector4& m1, const Vector4& m2, const Vector4& m3, const Vector4& m4);
  
  Matrix4x4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);

  Matrix4x4(const Matrix3x3& m);
  
public:
  
  Vector4 operator * (const Vector4& other) const;
  
  Matrix4x4 operator * (const Matrix4x4& other) const;

  void operator /= (float scalar);

  bool operator == (const Matrix4x4& other) const;
  
public:
  
  float const * valuePtr() const;
  
public:
  
  static Matrix4x4 IDENTITY;

public:
  
  float m11, m12, m13, m14, 
        m21, m22, m23, m24, 
        m31, m32, m33, m34, 
        m41, m42, m43, m44;
  
};

inline
float const * Matrix4x4::valuePtr() const {
  return &(m11);
}

#endif
