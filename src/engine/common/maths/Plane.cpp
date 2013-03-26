#include "Plane.h"

#include <math.h>

#include "Ray.h"

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

PlaneIntersectionResult Plane::testIntersection(const Ray& ray) {
  Vector3 b = ray.position + ray.direction * ray.length;
  Vector3 a = ray.position;
  Vector3 ab = b - a;
  
  float t = (d - normal().dot(a)) / normal().dot(ab);
  
  PlaneIntersectionResult result;
  
  result.intersected = t >= 0.0f && t <= 1.0f;
  result.position = a + ab * t;
  
  return result;
}