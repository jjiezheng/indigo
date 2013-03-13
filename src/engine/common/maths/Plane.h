#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"

class Plane {

public:

  Plane()
    : a(0), b(0), c(0), d(0) { }

  Plane(float a_, float b_, float c_, float d_)
    : a(a_), b(b_), c(c_), d(d_) { }

public:

  void normalize();

  Vector3 normal() const;

public:

  float a, b, c, d;
};

#endif
