#include "BoundingBox.h"

#include "Plane.h"
#include "Vector4.h"
#include "Ray.h"

bool BoundingBox::testIntersection(const Ray& ray) {
  Plane planes[6];
  planes[0] = Plane(0, 1, 0, min.y);
  planes[1] = Plane(0, 1, 0, max.y);
  planes[2] = Plane(1, 0, 0, min.x);
  planes[3] = Plane(1, 0, 0, max.x);
  planes[4] = Plane(0, 0, 1, min.z);
  planes[5] = Plane(0, 0, 1, max.z);

  Vector3 b = ray.position + ray.direction * ray.length;
  Vector3 a = ray.position;
  Vector3 ab = b - a;

  int intersections = 0;
  for (int i = 0; i < 6; i++) {
    float t = (planes[i].d - planes[i].normal().dot(a)) / planes[i].normal().dot(ab);

    if (t >= 0.0f && t <= 1.0f) {

      Vector3 q = a + ab * t;

      float kEpsilon = 0.0001f;

      bool isXInside = q.x >= min.x - kEpsilon && q.x <= max.x + kEpsilon;
      bool isYInside = q.y >= min.y - kEpsilon && q.y <= max.y + kEpsilon;
      bool isZInside = q.z >= min.z - kEpsilon && q.z <= max.z + kEpsilon;

      if (isXInside && isYInside && isZInside) {
        intersections++;
      }
    }
  }

  bool intersected = intersections > 1;

  return intersected;
}
