#ifndef QUATERNION_H
#define QUATERNION_H

#include "Matrix4x4.h"

class Vector3;

class Quaternion {
  
public:
  
  static Quaternion fromAxisAngle(const Vector3& axis, float angle);
  
public:
  
  Quaternion()
    : x(0.0f)
    , y(0.0f)
    , z(0.0f)
    , w(1.0f) { }
  
public:
  
  Matrix4x4 matrix4x4() const;
  
public:
  
  Quaternion operator * (const Quaternion& rhs) const;
  
private:

  float x, y, z, w;


};

#endif