#include "TranslateGizmo.h"

#include "../../Selection.h"

#include "maths/Vector4.h"

void TranslateGizmo::init() {
  view_.init();
}

void TranslateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

bool TranslateGizmo::selectFromRay(const Ray& ray) {
  bool result = view_.selectFromRay(ray);
  return result;
}

void TranslateGizmo::update(float dt, const Selection& selection) {
  if (selection.hasSelection()) {
    Matrix4x4 selectedLocalToWorld = selection.selection()->localToWorld();
    Vector4 selectedTranslation = selectedLocalToWorld.translation();
    Matrix4x4 viewLocalToWorld = Matrix4x4::translation(selectedTranslation);
    view_.setLocalToWorld(viewLocalToWorld);
  }
  else {
    isActive_ = false;
  }
}

bool TranslateGizmo::mousePick(const Ray& ray) {
  bool result = view_.selectFromRay(ray);
  return result;
}
