#ifndef Vector2_H_
#define Vector2_H_

class Vector2 {
  
public:
  
  Vector2();
  
  Vector2(float x, float y);
  
public:
  
  Vector2 operator - (const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
  }
  
public:
  
  float x, y;
  
public:
  
  static
  Vector2 IDENTITY;
  
};

#endif
