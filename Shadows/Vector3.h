#ifndef Shadows_Vector3_h
#define Shadows_Vector3_h

#include "Standard.h"

class Vector3 : public glm::vec3 {

public:
  
  Vector3()
    : glm::vec3()
  {
    
  }
  
  Vector3(float v_)
    : glm::vec3(v_)
  {
    
  }
  
  Vector3(const glm::vec3& v_)
    : glm::vec3(v_)
  {
    
  }
  
  Vector3(float x_, float y_, float z_)
    : glm::vec3(x_, y_, z_)
  {
    
  }
  
public:
  
  Vector3 rotateY(FLOAT angle) {
    return glm::gtx::rotate_vector::rotateY(*this, -angle);
  }
 
  Vector3 rotateX(FLOAT angle) {
    return glm::gtx::rotate_vector::rotateX(*this, angle);
  }
  
  Vector3 normalize() {
    glm::vec3 v(x, y, z);
    return glm::normalize(v);
  }
  
public:
  
  Vector3 operator * (const Matrix4x4& other) const {
    glm::vec4 result = glm::vec4(x, y, z, 1.0f) * other;
    return Vector3(result.x, result.y, result.z);
  }
  
public:
  
  static
  Vector3 IDENTITY;
  
  static
  Vector3 FORWARD;
  
  static
  Vector3 RIGHT;
    
  static
  Vector3 UP;
  
};

#endif
