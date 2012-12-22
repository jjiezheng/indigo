#include "Frustum.h"

#include "Matrix4x4.h"

void Frustum::rebuild(const Matrix4x4& viewProjection) {
  // Left plane
  planes_[0].a = viewProjection.m14 + viewProjection.m11;
  planes_[0].b = viewProjection.m24 + viewProjection.m21;
  planes_[0].c = viewProjection.m34 + viewProjection.m31;
  planes_[0].d = viewProjection.m44 + viewProjection.m41;

  // Right plane
  planes_[1].a = viewProjection.m14 - viewProjection.m11;
  planes_[1].b = viewProjection.m24 - viewProjection.m21;
  planes_[1].c = viewProjection.m34 - viewProjection.m31;
  planes_[1].d = viewProjection.m44 - viewProjection.m41;

  // Top plane
  planes_[2].a = viewProjection.m14 - viewProjection.m12;
  planes_[2].b = viewProjection.m24 - viewProjection.m22;
  planes_[2].c = viewProjection.m34 - viewProjection.m32;
  planes_[2].d = viewProjection.m44 - viewProjection.m42;

  // Bottom plane
  planes_[3].a = viewProjection.m14 + viewProjection.m12;
  planes_[3].b = viewProjection.m24 + viewProjection.m22;
  planes_[3].c = viewProjection.m34 + viewProjection.m32;
  planes_[3].d = viewProjection.m44 + viewProjection.m42;

  // Near plane
  planes_[4].a = viewProjection.m13;
  planes_[4].b = viewProjection.m23;
  planes_[4].c = viewProjection.m33;
  planes_[4].d = viewProjection.m43;

  // Far plane
  planes_[5].a = viewProjection.m14 - viewProjection.m13;
  planes_[5].b = viewProjection.m24 - viewProjection.m23;
  planes_[5].c = viewProjection.m34 - viewProjection.m33;
  planes_[5].d = viewProjection.m44 - viewProjection.m43;

  // Normalize planes
  for (int i = 0; i < 6; i++) {
    planes_[i].normalize();
  }
}

bool Frustum::testIntersect(const Vector3& point, float radius) {

  for (int i = 0; i < 6; i++) {
//    float result = planes_[i].normal().dot(point);
  }

  return false;
}
