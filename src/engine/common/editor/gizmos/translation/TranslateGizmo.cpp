#include "TranslateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"

void TranslateGizmo::init() {
  view_.init();
}

void TranslateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void TranslateGizmo::update(float dt, const Selection& selection, const Ray& mouseRay, const IViewer* const viewer) {
  view_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  Matrix4x4 selectedLocalToWorld = selection.selection()->localToWorld();
  Vector4 selectedTranslation = selectedLocalToWorld.translation();
  Matrix4x4 viewTranslation = Matrix4x4::translation(selectedTranslation) * Matrix4x4::translation(selection.selection()->boundingBox().mid());

  Vector3 viewerToGizmo = viewer->position() - view_.localToWorld().translation().vec3();
  float distanceToViewer = viewerToGizmo.length();
  Matrix4x4 viewScale = Matrix4x4::scale(distanceToViewer);

  Matrix4x4 viewLocalToWorld = viewTranslation * viewScale * Matrix4x4::scale(0.1f);
  view_.setLocalToWorld(viewLocalToWorld);
}

bool TranslateGizmo::mouseDown(const Ray& ray, const Selection& selection) {
  bool result = view_.selectFromRay(ray);
  return result;
}

void TranslateGizmo::mouseUp() {

}
