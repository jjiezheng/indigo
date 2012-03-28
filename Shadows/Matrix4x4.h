#ifndef MATRIX4x4_H
#define MATRIX4x4_H

class Vector4;
class Vector3;
class Matrix3x3;

class Matrix4x4 {
  
public:
  
  static
  Matrix4x4 rotationX(int degrees);
  
  static
  Matrix4x4 rotationX(float radians);
    
  static
  Matrix4x4 rotationY(int degrees);
  
  static
  Matrix4x4 rotationY(float radians);

  static
  Matrix4x4 rotationZ(int degrees);
  
  static
  Matrix4x4 rotationZ(float radians);  
  
  static 
  Matrix4x4 translation(const Vector4& v);
  
  static
  Matrix4x4 perspective(float fov, float aspect, float znear, float zfar);
  
  static
  Matrix4x4 orthographic(float left, float right, float bottom, float top, float near, float far);
  
public:
  
  std::string toString() const;
  
  Matrix4x4 inverse() const;
  
  Matrix3x3 mat3x3() const;
  
public:
  
  Matrix4x4(float m11, float m12, float m13, float m14,
            float m21, float m22, float m23, float m24,
            float m31, float m32, float m33, float m34,
            float m41, float m42, float m43, float m44);
  
public:
  
  Vector4 operator * (const Vector4& other) const;
  
  Matrix4x4 operator * (const Matrix4x4& other) const;
  
public:
  
  float const * valuePtr() const;
  
public:
  
  static
  Matrix4x4 IDENTITY;
  
private:
  
  Matrix4x4();  
  
private:
  
  float m11_, m12_, m13_, m14_, 
        m21_, m22_, m23_, m24_, 
        m31_, m32_, m33_, m34_, 
        m41_, m42_, m43_, m44_;
  
};

inline
float const * Matrix4x4::valuePtr() const {
  return &(m11_);
}


#endif