#ifndef MATRIX3x3_H
#define MATRIX3x3_H

class Vector3;

class Matrix3x3 {
 
public:

  static Matrix3x3 rotation(const Vector3& axis, float angleRadians);

  static Matrix3x3 rotationX(float radians);

  static Matrix3x3 rotationY(float radians);

  static Matrix3x3 rotationZ(float radians); 

public:

  static Matrix3x3 scale(const Vector3& scale);

public:

  Matrix3x3 inverseTranspose() const;
  
public:
  
  Vector3 operator * (const Vector3& other) const;
  
public:
  
  float const * valuePtr() const;
  
public:
  
  Matrix3x3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float m31, float m32, float m33);

  static Matrix3x3 IDENTITY;
  
private:
  
  Matrix3x3();  

public:
  
  float m11, m12, m13, m21, m22, m23, m31, m32, m33;
  
};

inline float const * Matrix3x3::valuePtr() const {
  return &(m11);
}

#endif
