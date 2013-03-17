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

bool TranslateGizmoView::selectFromRay(const Ray& ray) {
  IntersectionResult zResult = zArrow_.testIntersect(ray);

  bool result = false;

  if (zResult.intersected) {
    LOG(LOG_CHANNEL_EDITOR, "Z Intersected");
    return true;
  }


  // find which arrow is closest
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

  return false;
}
