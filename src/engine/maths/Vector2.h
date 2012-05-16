#ifndef Vector2_H_
#define Vector2_H_

#include <string>

class Vector2 {
  
public:
  
  static Vector2 IDENTITY;
  
public:
  
  Vector2();
  
  Vector2(float x, float y);
  
public:
  
  Vector2 operator - (const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
  }
  
public:
  
  float aspectRatio() const;

public:

  std::string toString() const;
  
public:
  
  float x, y;
      
};

inline float Vector2::aspectRatio() const {
  return x / y;
}

#endif
