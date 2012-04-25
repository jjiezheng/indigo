#ifndef MATRIX3x3_H
#define MATRIX3x3_H

class Vector3;

class Matrix3x3 {
 
public:
  
  static
  Matrix3x3 rotationX(int degrees);
  
  static
  Matrix3x3 rotationY(int degrees);
  
public:
  
  Vector3 operator * (const Vector3& other) const;
  
public:
  
  float const * valuePtr() const;
  
public:
  
  Matrix3x3(float m11, float m12, float m13,
            float m21, float m22, float m23,
            float m31, float m32, float m33);
  
private:
  
  Matrix3x3();  
  
private:
  
  float m11_, m12_, m13_, m21_, m22_, m23_, m31_, m32_, m33_;
  
};

inline
float const * Matrix3x3::valuePtr() const {
  return &(m11_);
}

#endif
