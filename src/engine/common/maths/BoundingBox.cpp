#include "BoundingBox.h"

#include "Plane.h"
#include "Vector4.h"
#include "Ray.h"
#include "IntersectionResult.h"

IntersectionResult BoundingBox::testIntersection(const Ray& ray) {
  Plane planes[6];
  planes[0] = Plane(0, 1, 0, min.y);
  planes[1] = Plane(0, 1, 0, max.y);
  planes[2] = Plane(1, 0, 0, min.x);
  planes[3] = Plane(1, 0, 0, max.x);
  planes[4] = Plane(0, 0, 1, min.z);
  planes[5] = Plane(0, 0, 1, max.z);

	IntersectionResult result;

  int intersections = 0;
  for (int i = 0; i < 6; i++) {
    PlaneIntersectionResult planeResult = planes[i].testIntersection(ray);
    
    if (planeResult.intersected) {
    
      float kEpsilon = 0.0001f;

      bool isXInside = planeResult.position.x >= min.x - kEpsilon && planeResult.position.x <= max.x + kEpsilon;
      bool isYInside = planeResult.position.y >= min.y - kEpsilon && planeResult.position.y <= max.y + kEpsilon;
      bool isZInside = planeResult.position.z >= min.z - kEpsilon && planeResult.position.z <= max.z + kEpsilon;

      if (isXInside && isYInside && isZInside) {
        intersections++;

				if (intersections > 1) {
					result.intersected = true;
					result.distance = planeResult.position.length();
				}
      }
    }
  }

	return result;
}

Vector3 BoundingBox::mid() const {
  Vector3 midPoint = (min + max) / 2.0f;
  return midPoint;
}
