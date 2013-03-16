#include "TranslateGizmoView.h"

#include "renderer/GraphicsInterface.h"

#include "maths/Angles.h"
#include "maths/Matrix4x4.h"

#include "io/Log.h"

void TranslateGizmoView::init() {
  xArrow_.init();
  xArrow_.setLocalToWorld(Matrix4x4::rotationY(toRadians(90)));
  
  yArrow_.init();
  yArrow_.setLocalToWorld(Matrix4x4::rotationX(toRadians(-90)));

  zArrow_.init();
}

void TranslateGizmoView::render(IViewer* viewer) {
  GraphicsInterface::beginPerformanceEvent("Translate Gizmo");
  
  xArrow_.render(viewer);
  yArrow_.render(viewer);
  zArrow_.render(viewer);

  GraphicsInterface::endPerformanceEvent();
}

bool TranslateGizmoView::selectFromRay(const Ray& ray) {
  IntersectionResult xResult = xArrow_.testIntersect(ray);

  if (xResult.intersected) {
    LOG(LOG_CHANNEL_EDITOR, "X Intersected");
    return true;
  }

  IntersectionResult yResult = yArrow_.testIntersect(ray);

  if (yResult.intersected) {
    LOG(LOG_CHANNEL_EDITOR, "Y Intersected");
    return true;
  }

  IntersectionResult zResult = zArrow_.testIntersect(ray);

  bool result = false;

  if (zResult.intersected) {
    LOG(LOG_CHANNEL_EDITOR, "Z Intersected");
    return true;
  }

  return false;
}
