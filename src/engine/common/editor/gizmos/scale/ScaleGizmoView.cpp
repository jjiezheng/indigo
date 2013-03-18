#include "ScaleGizmoView.h"

#include "renderer/GraphicsInterface.h"

#include "maths/Angles.h"
#include "maths/Matrix4x4.h"

#include "io/Log.h"

void ScaleGizmoView::init() {
  xBox_.init();
  xBox_.setLocalToWorld(Matrix4x4::rotationY(toRadians(90)));
  addChild(&xBox_);

  yBox_.init();
  yBox_.setLocalToWorld(Matrix4x4::rotationX(toRadians(-90)));
  addChild(&yBox_);

  zBox_.init();
  addChild(&zBox_);

  allBox_.init();
  addChild(&allBox_);
}

void ScaleGizmoView::render(IViewer* viewer) const {
  GraphicsInterface::beginPerformanceEvent("Scale Gizmo");

  xBox_.render(viewer);
  yBox_.render(viewer);
  zBox_.render(viewer);
  allBox_.render(viewer);

  GraphicsInterface::endPerformanceEvent();
}

ScaleGizmoSelectionResult ScaleGizmoView::selectFromRay(const Ray& ray) {
  ScaleGizmoSelectionResult result;

  IntersectionResult allResult = allBox_.testIntersect(ray);

  if (allResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_ALL;
    result.selected = true;
    return result;
  }

  IntersectionResult zResult = zBox_.testIntersect(ray);

  if (zResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_Z;
    result.selected = true;
  }

  IntersectionResult yResult = yBox_.testIntersect(ray);

  if (yResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_Y;
    result.selected = true;
  }

  IntersectionResult xResult = xBox_.testIntersect(ray);

  if (xResult.intersected) {
    result.mode = SCALE_GIZMO_MODE_X;
    result.selected = true;
  }

  return result;
}

void ScaleGizmoView::highlightFromRay(const Ray& ray) {
  IntersectionResult allResult = allBox_.testIntersect(ray);
  allBox_.setHighlight(allResult.intersected);

  if (allResult.intersected) {
    return;
  }

  IntersectionResult zResult = zBox_.testIntersect(ray);
  zBox_.setHighlight(zResult.intersected);

  IntersectionResult yResult = yBox_.testIntersect(ray);
  yBox_.setHighlight(yResult.intersected);

  IntersectionResult xResult = xBox_.testIntersect(ray);
  xBox_.setHighlight(xResult.intersected);
}

void ScaleGizmoView::highlightX() {
  xBox_.setHighlight(true);
}

void ScaleGizmoView::highlightY() {
  yBox_.setHighlight(true);
}

void ScaleGizmoView::highlightZ() {
  zBox_.setHighlight(true);
}

void ScaleGizmoView::highlightAll() {
  allBox_.setHighlight(true);
}
