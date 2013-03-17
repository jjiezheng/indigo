#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

class Vector3 {
  
public:
  
  Vector3();
  
  Vector3(float x_, float y_, float z_);
  
public:
  
  static Vector3 IDENTITY;
  
  static Vector3 FORWARD;
  
  static Vector3 RIGHT;
    
  static Vector3 UP;
  
public:

  float dot(const Vector3& other) const;

  Vector3 cross(const Vector3& other) const;

  Vector3 normalize() const;

	void normalizeIP();

	float angleBetween(const Vector3& other) const;

  Vector3 inverse() const;

  float length() const;
  
  float distance(const Vector3& other) const;

public:
  
  Vector3 rotateX(float degrees);
  
  Vector3 rotateY(float degrees);
  
public:
  
  std::string toString() const;
  
public:
  
  float x, y, z;
  
public:
  
  inline float const * valuePtr() const;
  
  Vector3 operator + (const Vector3& other) const;

  Vector3 operator - (const Vector3& other) const;
  
  Vector3 operator * (float scalar) const;

  Vector3 operator / (float scalar) const;

	Vector3 operator * (const Vector3& other) const;
  
  Vector3 operator - () const;
  
};

float const * Vector3::valuePtr() const {
  return &(x);
}


#endif
