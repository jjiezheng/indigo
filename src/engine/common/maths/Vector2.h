#ifndef Vector2_H_
#define Vector2_H_

#include <string>

class Point;

class Vector2 {
  
public:
  
  static Vector2 IDENTITY;
  
public:
  
  Vector2();

  Vector2(const Point& p);
  
  Vector2(float x, float y);
  
public:
  
  Vector2 operator - (const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
  }

  Vector2 operator * (const Vector2& other) const {
    return Vector2(x * other.x, y * other.y);
  }
  
public:
  
  float aspectRatio() const;

	Vector2 normalize() const;

	void normalizeIP();

	float length() const;

	float dot(const Vector2& other) const;

	float angleBetween(const Vector2& other) const;

  float const * valuePtr() const;

public:

  std::string toString() const;
  
public:
  
  float x, y;
      
};

inline float const * Vector2::valuePtr() const {
  return &(x);
}


inline float Vector2::aspectRatio() const {
  return x / y;
}

inline float Vector2::dot(const Vector2& other) const {
	return x * other.x + y * other.y;
}

#endif
