#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray {

public:

  Ray(const Vector3& position_, const Vector3& direction_, float length_)
    : position(position_)
    , direction(direction_)
    , length(length_)
  { }

public:

  Vector3 position;
  Vector3 direction;
  float length;

};

#endif