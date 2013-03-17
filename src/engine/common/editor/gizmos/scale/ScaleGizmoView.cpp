#include "ScaleGizmoView.h"

#include "renderer/GraphicsInterface.h"

#include "maths/Angles.h"
#include "maths/Matrix4x4.h"

#include "io/Log.h"

void ScaleGizmoView::init() {
  xArrow_.init();
  xArrow_.setLocalToWorld(Matrix4x4::rotationY(toRadians(90)));
  addChild(&xArrow_);

  yArrow_.init();
  yArrow_.setLocalToWorld(Matrix4x4::rotationX(toRadians(-90)));
  addChild(&yArrow_);

  zArrow_.init();
  addChild(&zArrow_);
}

void ScaleGizmoView::render(IViewer* viewer) const {
  GraphicsInterface::beginPerformanceEvent("Translate Gizmo");

  xArrow_.render(viewer);
  yArrow_.render(viewer);
  zArrow_.render(viewer);

  GraphicsInterface::endPerformanceEvent();
}

ScaleGizmoSelectionResult ScaleGizmoView::selectFromRay(const Ray& ray) {
  ScaleGizmoSelectionResult result;

  IntersectionResult zResult = zArrow_.testIntersect(ray);

  if (zResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_Z;
    result.selected = true;
  }

  IntersectionResult yResult = yArrow_.testIntersect(ray);

  if (yResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_Y;
    result.selected = true;
  }

  IntersectionResult xResult = xArrow_.testIntersect(ray);

  if (xResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_X;
    result.selected = true;
  }

  return result;
}

void ScaleGizmoView::highlightFromRay(const Ray& ray) {
  IntersectionResult zResult = zArrow_.testIntersect(ray);
  zArrow_.setHighlight(zResult.intersected);

  IntersectionResult yResult = yArrow_.testIntersect(ray);
  yArrow_.setHighlight(yResult.intersected);

  IntersectionResult xResult = xArrow_.testIntersect(ray);
  xArrow_.setHighlight(xResult.intersected);
}

void ScaleGizmoView::highlightX() {
  xArrow_.setHighlight(true);
}

void ScaleGizmoView::highlightY() {
  yArrow_.setHighlight(true);
}

void ScaleGizmoView::highlightZ() {
  zArrow_.setHighlight(true);
}
