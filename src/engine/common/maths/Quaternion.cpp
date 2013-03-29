#include "Quaternion.h"

#include <math.h>

#include "Vector3.h"

Quaternion Quaternion::fromAxisAngle(const Vector3& axis, float angle) {
  float epsilon = sin(angle / 2.0f);
  
  Quaternion quaternion;
  quaternion.x = axis.x * epsilon;
  quaternion.y = axis.y * epsilon;
  quaternion.z = axis.z * epsilon;
  quaternion.w = cos(angle / 2.0f);
  
  return quaternion;
}

Quaternion Quaternion::operator * (const Quaternion& rhs) const {
  Quaternion result;
  result.x = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
  result.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
  result.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
  result.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
  return result;
}

Matrix4x4 Quaternion::matrix4x4() const {
  Matrix4x4 result;
  
  result.m11 = w * w + x * x - y * y - z * z;
  result.m12 = 2.0f * x * y - 2.0f * w * z;
  result.m13 = 2.0f * x * z + 2.0f * w * y;
  result.m14 = 0.0f;
  
  result.m21 = 2.0f * x * y - 2.0f * w * z;
  result.m22 = w * w  - x * x + y * y - z * z;
  result.m23 = 2.0f * y * z - 2.0f * w * x;
  result.m24 = 0.0f;
  
  result.m31 = 2.0f * x * z - 2.0f * w * y;
  result.m32 = 2.0f * y * z - 2.0f * w * x;
  result.m33 = w * w - x * x - y * y + z * z;
  result.m34 = 0.0f;
  
  result.m41 = 0.0f;
  result.m42 = 0.0f;
  result.m43 = 0.0f;
  result.m44 = 1.0f;
  
  return result;
}


