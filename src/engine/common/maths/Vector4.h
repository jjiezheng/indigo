#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>

class Vector3;
class Vector2;

class Vector4 {
  
public:
  
  Vector4();

  Vector4(const Vector2& v);
  
  Vector4(const Vector3& v);

  Vector4(const Vector3& v, float w_);
  
  Vector4(float x_, float y_, float z_, float w_);
  
public:
  
  static Vector4 IDENTITY;
  
  static Vector4 FORWARD;
  
  static Vector4 RIGHT;
  
  static Vector4 UP;

public:

  Vector3 vec3() const;
  
public:
  
  Vector4 rotateX(float degrees);
  
  Vector4 rotateY(float degrees);
  
public:

  float distance(const Vector4& other) const;

  float length() const;

  Vector4 inverse() const;

  Vector4 normalize() const;

  void normalizeIP();

public:

  Vector4 cross(const Vector4& other) const;

  float dot(const Vector4& other) const;

  float angle(const Vector4& other) const;

public:
  
  std::string toString() const;
  
public:
  
  float x, y, z, w;
  
public:
  
  inline float const * valuePtr() const;
  
  Vector4 operator + (const Vector4& other) const;

  Vector4 operator - (const Vector4& other) const;

  Vector4 operator * (const Vector4& other) const;

  Vector4 operator / (const Vector4& other) const;

  
  Vector4 operator * (float scalar) const;

  Vector4 operator / (float scalar) const;

  Vector4 operator - (float scalar) const;

  Vector4 operator + (float scalar) const;


  void operator += (const Vector4& other);
  
  void operator /= (float scalar);
  
  bool operator == (const Vector4& other) const;

  bool operator != (const Vector4& other) const;

  Vector4 operator -() const;
  
};

float const * Vector4::valuePtr() const {
  return &(x);
}

#endif
