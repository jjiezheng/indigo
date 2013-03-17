#include "TranslateGizmoView.h"

#include "renderer/GraphicsInterface.h"

#include "maths/Angles.h"
#include "maths/Matrix4x4.h"

#include "io/Log.h"

void TranslateGizmoView::init() {
  xArrow_.init();
  xArrow_.setLocalToWorld(Matrix4x4::rotationY(toRadians(90)));
  addChild(&xArrow_);
  
  yArrow_.init();
  yArrow_.setLocalToWorld(Matrix4x4::rotationX(toRadians(-90)));
  addChild(&yArrow_);

  zArrow_.init();
  addChild(&zArrow_);
}

void TranslateGizmoView::render(IViewer* viewer) const {
  GraphicsInterface::beginPerformanceEvent("Translate Gizmo");
  
  xArrow_.render(viewer);
  yArrow_.render(viewer);
  zArrow_.render(viewer);

  GraphicsInterface::endPerformanceEvent();
}

TranslateGizmoSelectionResult TranslateGizmoView::selectFromRay(const Ray& ray) {
  TranslateGizmoSelectionResult result;

  IntersectionResult zResult = zArrow_.testIntersect(ray);

  if (zResult.intersected) {
    result.mode = TRANSLATE_GIZMO_MODE_Z;
    result.selected = true;
  }

  IntersectionResult yResult = yArrow_.testIntersect(ray);

  if (yResult.intersected) {
    result.mode = TRANSLATE_GIZMO_MODE_Y;
    result.selected = true;
  }

  IntersectionResult xResult = xArrow_.testIntersect(ray);

  if (xResult.intersected) {
    result.mode = TRANSLATE_GIZMO_MODE_X;
    result.selected = true;
  }

  return result;
}

void TranslateGizmoView::highlightFromRay(const Ray& ray) {
  IntersectionResult zResult = zArrow_.testIntersect(ray);
  zArrow_.setHighlight(zResult.intersected);

  IntersectionResult yResult = yArrow_.testIntersect(ray);
  yArrow_.setHighlight(yResult.intersected);

  IntersectionResult xResult = xArrow_.testIntersect(ray);
  xArrow_.setHighlight(xResult.intersected);
}
