#include "ScaleGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void ScaleGizmo::init() {
  view_.init();
}

void ScaleGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void ScaleGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* const viewer) {
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

  Vector3 planePosition = startSelectionPosition_;

  Point mouseDelta = mousePosition - startMousePosition_;

  Point planeScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), planePosition);
  planeScreenSpace = planeScreenSpace + mouseDelta;

  Vector4 newPlanePosition = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), planeScreenSpace, planeScreenSpace.z);
  Vector3 planeDelta = newPlanePosition.vec3() - lastSelectionPosition_;

  if (planeDelta.length() > 0.01f) {
    float planePositionDeltaLength = 0.1f;
    if (newPlanePosition.x < lastSelectionPosition_.x) {
      planePositionDeltaLength += -planePositionDeltaLength;
    }


    if (newPlanePosition.length() < planePosition.length()) {
      planePositionDeltaLength = -planePositionDeltaLength;
    }

    if (translateMode_ == SCALE_GIZMO_MODE_X) {
      selectedLocalToWorld.m11 += planePositionDeltaLength;
      view_.highlightX();
    }

    if (translateMode_ == SCALE_GIZMO_MODE_Y) {
      //selectedLocalToWorld.m22 = newPlaneScale.y;
      view_.highlightY();
    }

    if (translateMode_ == SCALE_GIZMO_MODE_Z) {
      //selectedLocalToWorld.m33 = newPlaneScale.z;  
      view_.highlightZ();
    }
  }

 

  lastMousePosition_ = mousePosition;
  lastSelectionPosition_ = newPlanePosition.vec3();


  selection.selection()->setLocalToWorld(selectedLocalToWorld);

}

bool ScaleGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  ScaleGizmoSelectionResult result = view_.selectFromRay(mouseRay);
  translateMode_ = result.mode;
  return result.selected;
}

void ScaleGizmo::mouseUp() {
  translateMode_ = SCALE_GIZMO_MODE_UNKNOWN;
}
