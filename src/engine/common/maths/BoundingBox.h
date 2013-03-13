#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "Vector3.h"

class Ray;

class BoundingBox {

public:

	Vector3 min;
	Vector3 max;

public:

  bool testIntersection(const Ray& ray);

};

#endif
