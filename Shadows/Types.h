#ifndef CubeFX_Types_h
#define CubeFX_Types_h

#define INT int
#define UINT unsigned int
#define BOOLEAN bool
#define CHAR char
#define DOUBLE double
#define FLOAT float

#include <inttypes.h>
#define BYTE uint8_t
#define WORD uint16_t
#define DWORD uint32_t
#define LONG long

#define Matrix4x4 glm::mat4

#define MAT3 glm::mat3
#define MAT4 glm::mat4
#define VEC2 glm::vec2
#define Vector2 glm::vec2
#define VEC3 Vector3
#define VEC4 glm::vec4

#define Color3 glm::vec3

#define INVALID -1

struct Rectangle {
  Rectangle(float x_, float y_, float width_, float height_) 
  : width(width_), height(height_)
  , x(x_), y(y_) { }

  Rectangle() 
  : width(0)
  , height(0)
  , x(0)
  , y(0) { }
  
  float width;
  float height;
  float x;
  float y;
};

#endif
