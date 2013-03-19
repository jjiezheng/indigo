#include "RotateGizmoView.h"

#include "maths/Angles.h"

void RotateGizmoView::init() {
  xRing_.init();
  zRing_.setLocalToWorld(Matrix4x4::rotationY(toRadians(90)));

  yRing_.init();
  yRing_.setLocalToWorld(Matrix4x4::rotationX(toRadians(-90)));

  zRing_.init();
}

void RotateGizmoView::render(IViewer* viewer) const {
  xRing_.render(viewer);
  yRing_.render(viewer);
  zRing_.render(viewer);
}

void RotateGizmoView::highlightFromRay(const Ray& ray) {
  IntersectionResult xResult = xRing_.testIntersect(ray);
  xRing_.setHighlight(xResult.intersected);

  IntersectionResult yResult = yRing_.testIntersect(ray);
  yRing_.setHighlight(yResult.intersected);

  IntersectionResult zResult = zRing_.testIntersect(ray);
  zRing_.setHighlight(zResult.intersected);
}
