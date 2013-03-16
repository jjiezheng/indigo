#include "TranslateGizmo.h"

void TranslateGizmo::init() {
  view_.init();
}

void TranslateGizmo::render(IViewer* viewer) {
  view_.render(viewer);
}

bool TranslateGizmo::selectFromRay(const Ray& ray) {
  bool result = view_.selectFromRay(ray);
  return result;
}
