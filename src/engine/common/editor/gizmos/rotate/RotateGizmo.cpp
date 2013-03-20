#include "RotateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void RotateGizmo::init() {
  isActive_ = false;
  view_.init();
}

void RotateGizmo::render(IViewer* viewer) const {
  view_.render(viewer);
}

void RotateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer) {
  view_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  Matrix4x4 selectedLocalToWorld = selection.selection()->localToWorld();
  Matrix4x4 viewTranslation = selection.selection()->localToWorld();

  Vector3 viewerToGizmo = viewer->position() - view_.localToWorld().translation().vec3();
  float distanceToViewer = viewerToGizmo.length();
  Matrix4x4 viewScale = Matrix4x4::scale(distanceToViewer);

  Matrix4x4 viewLocalToWorld = viewScale * Matrix4x4::scale(0.1f);

  //

  if (startMousePosition_.x != 0 || startMousePosition_.y != 0) {

    Vector3 planePosition = startSelectionPosition_;

    Point mouseDelta = mousePosition - startMousePosition_;

    Point planeScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), planePosition);
    planeScreenSpace = planeScreenSpace + mouseDelta;

    Vector4 newPlanePosition = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), planeScreenSpace, planeScreenSpace.z);
    Vector3 planeDelta = newPlanePosition.vec3() - lastSelectionPosition_;

    float kMinimumDragLength = 0.001f;
    if (planeDelta.length() > kMinimumDragLength) {

      float kScaleAmountScaler = 0.5f;
      float planePositionDeltaLength = planeDelta.length() * kScaleAmountScaler;

      if (rotateMode_ == ROTATE_GIZMO_MODE_X) {
        if (newPlanePosition.y < lastSelectionPosition_.y) {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationX(planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationX(planePositionDeltaLength);
        } else {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationX(-planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationX(-planePositionDeltaLength);
        }
      }

      if (rotateMode_ == ROTATE_GIZMO_MODE_Y) {
        if (newPlanePosition.x < lastSelectionPosition_.x) {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationY(-planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationY(-planePositionDeltaLength);
        } else {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationY(planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationY(planePositionDeltaLength);
        }
      }

      if (rotateMode_ == ROTATE_GIZMO_MODE_Z) {
        if (newPlanePosition.y < lastSelectionPosition_.y) {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationZ(-planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationZ(-planePositionDeltaLength);
        } else {
          viewOrientation_ = viewOrientation_ * Matrix4x4::rotationZ(planePositionDeltaLength);
          selectedLocalToWorld = selectedLocalToWorld * Matrix4x4::rotationZ(planePositionDeltaLength);
        }
      }
    }

    lastSelectionPosition_ = newPlanePosition.vec3();
    selection.selection()->setLocalToWorld(selectedLocalToWorld);
  }

   viewLocalToWorld = viewTranslation * viewOrientation_ * viewLocalToWorld;
   view_.setLocalToWorld(viewLocalToWorld);
   

  if (rotateMode_ == ROTATE_GIZMO_MODE_X) {
    view_.highlightX();
  }

  if (rotateMode_ == ROTATE_GIZMO_MODE_Y) {
    view_.highlightY();
  }

  if (rotateMode_ == ROTATE_GIZMO_MODE_Z) {
    view_.highlightZ();
  }
}

bool RotateGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  lastSelectionPosition_ = startSelectionPosition_;

  RotateGizmoSelectionResult result = view_.selectFromRay(mouseRay);
  rotateMode_ = result.mode;
  return result.selected;
}

void RotateGizmo::mouseUp() {
  rotateMode_ = ROTATE_GIZMO_MODE_UNKNOWN;
}
