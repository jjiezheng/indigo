#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3.h"
#include "IntersectionResult.h"

class Ray;

class BoundingBox {

public:

	Vector3 min;
	Vector3 max;

public:

  Vector3 mid() const;

public:

  IntersectionResult testIntersection(const Ray& ray);

};

#endif
