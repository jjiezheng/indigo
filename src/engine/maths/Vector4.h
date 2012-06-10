#ifndef VECTOR4_H
#define VECTOR4_H

#include <string>

class Vector3;

class Vector4 {
  
public:
  
  Vector4();
  
  Vector4(const Vector3& v);
  
  Vector4(float x_, float y_, float z_);
  
  Vector4(float x_, float y_, float z_, float w_);
  
public:
  
  static
  Vector4 IDENTITY;
  
  static
  Vector4 FORWARD;
  
  static
  Vector4 RIGHT;
  
  static
  Vector4 UP;
  
public:
  
  Vector4 rotateX(int degrees);
  
  Vector4 rotateY(int degrees);
  
public:

  float distance(const Vector4& other) const;

  float length() const;

public:
  
  std::string toString() const;
  
public:
  
  float x, y, z, w;
  
public:
  
  inline float const * valuePtr() const;
  
  Vector4 operator + (const Vector4& other) const;

  Vector4 operator - (const Vector4& other) const;
  
  Vector4 operator * (float scalar) const;
  
  Vector4 operator == (const Vector4& other) const;
  
};

float const * Vector4::valuePtr() const {
  return &(x);
}

#endif
