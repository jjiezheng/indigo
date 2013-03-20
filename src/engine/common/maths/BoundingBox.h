#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3.h"
#include "IntersectionResult.h"

class Ray;

class BoundingBox {

public:

  BoundingBox() { }

  BoundingBox(const Vector3& min_, const Vector3& max_)
    : min(min_)
    , max(max_) { }

public:

	Vector3 min;
	Vector3 max;

public:

  BoundingBox operator + (const BoundingBox& other);

public:

  Vector3 mid() const;

public:

  IntersectionResult testIntersection(const Ray& ray);

};

inline BoundingBox BoundingBox::operator + (const BoundingBox& other) {
  BoundingBox result;
  result.min = min + other.min;
  result.max = max + other.max;
  return result;
}

#endif
