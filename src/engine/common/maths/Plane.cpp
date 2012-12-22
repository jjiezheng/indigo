#include "Plane.h"

#include <math.h>

Vector3 Plane::normal() const {
  return Vector3(a, b, c);
}

void Plane::normalize()  {
  float magnitude = sqrtf(a * a + b * b + c * c);

  if (magnitude) {
    a /= magnitude;
    b /= magnitude;
    c /= magnitude;
    d /= magnitude;
  } else {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
  }
}