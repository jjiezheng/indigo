#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "Plane.h"

class Matrix4x4;
class Vector3;

class Frustum {

public:

  void rebuild(const Matrix4x4& viewProjection);

  bool testIntersect(const Vector3& point, float radius);

private:

  Plane planes_[6];

};

#endif