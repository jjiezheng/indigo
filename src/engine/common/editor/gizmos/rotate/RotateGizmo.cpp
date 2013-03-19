#include "RotateGizmo.h"

void RotateGizmo::init() {
  isActive_ = true;
  view_.init();
}

void RotateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void RotateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer) {
  view_.highlightFromRay(mouseRay);
}

bool RotateGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  return false;
}

void RotateGizmo::mouseUp() {

}
