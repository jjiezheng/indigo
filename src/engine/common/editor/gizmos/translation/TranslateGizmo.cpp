#include "TranslateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void TranslateGizmo::init() {
  view_.init();
}

void TranslateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void TranslateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* const viewer) {
  view_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  Matrix4x4 selectedLocalToWorld = selection.selection()->localToWorld();
  Vector4 selectedTranslation = selectedLocalToWorld.translation();
  Vector4 selectedMidPoint = selection.selection()->boundingBox().mid();
  Matrix4x4 viewTranslation = Matrix4x4::translation(selectedTranslation) * Matrix4x4::translation(selectedMidPoint);

  Vector3 viewerToGizmo = viewer->position() - view_.localToWorld().translation().vec3();
  float distanceToViewer = viewerToGizmo.length();
  Matrix4x4 viewScale = Matrix4x4::scale(distanceToViewer);

  Matrix4x4 viewLocalToWorld = viewTranslation * viewScale * Matrix4x4::scale(0.1f);
  view_.setLocalToWorld(viewLocalToWorld);

  Vector3 planePosition(0, 0, 0);

  Point planeScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), planePosition);
  planeScreenSpace.x += mousePosition.x - startPosition_.x;
  planeScreenSpace.y += mousePosition.y - startPosition_.y;

  Vector4 newPlanePosition = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), planeScreenSpace, planeScreenSpace.z);

  if (translateMode_ == TRANSLATE_GIZMO_MODE_X) {
    selectedLocalToWorld.m14 = newPlanePosition.x;
    view_.highlightX();
  }

  if (translateMode_ == TRANSLATE_GIZMO_MODE_Y) {
    selectedLocalToWorld.m24 = newPlanePosition.y;
    view_.highlightY();
  }

  if (translateMode_ == TRANSLATE_GIZMO_MODE_Z) {
    selectedLocalToWorld.m34 = newPlanePosition.z;  
    view_.highlightZ();
  }

  selection.selection()->setLocalToWorld(selectedLocalToWorld);

}

bool TranslateGizmo::mouseDown(const Point& mousePosition, const Ray& mouseRay) {
  startPosition_ = mousePosition;
  TranslateGizmoSelectionResult result = view_.selectFromRay(mouseRay);
  translateMode_ = result.mode;
  return result.selected;
}

void TranslateGizmo::mouseUp() {
  translateMode_ = TRANSLATE_GIZMO_MODE_UNKNOWN;
}
