#ifndef Shadows_Vector3_h
#define Shadows_Vector3_h

class Vector3 {
  
public:
  
  Vector3();
  
  Vector3(float x_, float y_, float z_);
  
public:
  
  static
  Vector3 IDENTITY;
  
  static
  Vector3 FORWARD;
  
  static
  Vector3 RIGHT;
    
  static
  Vector3 UP;
  
public:
  
  Vector3 rotateX(int degrees);
  
  Vector3 rotateY(int degrees);
  
public:
  
  std::string toString() const;
  
public:
  
  float x, y, z;
  
public:
  
  inline float const * valuePtr() const;
  
  Vector3 operator + (const Vector3& other) const;
  
  Vector3 operator * (float scalar) const;
  
  Vector3 operator - () const;
  
};

float const * Vector3::valuePtr() const {
  return &(x);
}


#endif
