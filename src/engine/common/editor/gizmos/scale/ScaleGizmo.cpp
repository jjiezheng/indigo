#include "ScaleGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "renderer/Transforms.h"

void ScaleGizmo::init() {
  view_ = &scaleView_;
  scaleView_.init();
}

void ScaleGizmo::render(IViewer* viewer) const {
  scaleView_.render(viewer);
}

void ScaleGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* const viewer) {
  Gizmo::update(dt, selection, mousePosition, mouseRay, viewer);
  
  scaleView_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }

  Node* selectedNode = selection.selection();
  Quaternion selectedOrientation = selectedNode->orientation();
  scaleView_.setOrientation(selectedOrientation);

  //

  if (startMousePosition_.x == 0 || startMousePosition_.y == 0) {
    return;
  }

  Vector3 planePosition = startSelectionPosition_;

  Point mouseDelta = mousePosition - startMousePosition_;

  Point planeScreenSpace = Transforms::worldSpaceToScreenSpace(viewer->viewProjection(), planePosition);
  planeScreenSpace = planeScreenSpace + mouseDelta;

  Vector4 newPlanePosition = Transforms::screenSpaceToWorldSpace(viewer->viewProjection().inverse(), planeScreenSpace, planeScreenSpace.z);
  Vector3 planeDelta = newPlanePosition.vec3() - lastSelectionPosition_;
  
  Vector3 selectedScale(1, 1, 1);

  float kMinimumDragLength = 0.001f;
  if (planeDelta.length() > kMinimumDragLength) {

    float kScaleAmountScaler = 0.5f;
    float planePositionDeltaLength = planeDelta.length() * kScaleAmountScaler;

    if (scaleMode_ == SCALE_GIZMO_MODE_X) {
      if (newPlanePosition.x < lastSelectionPosition_.x) {
        selectedScale.x -= planePositionDeltaLength;
      } else {
        selectedScale.x += planePositionDeltaLength;
      }
    }

    if (scaleMode_ == SCALE_GIZMO_MODE_Y) {
      if (newPlanePosition.y < lastSelectionPosition_.y) {
        selectedScale.y -= planePositionDeltaLength;
      } else {
        selectedScale.y += planePositionDeltaLength;
      }
    }

    if (scaleMode_ == SCALE_GIZMO_MODE_Z) {
      if (newPlanePosition.z < lastSelectionPosition_.z) {
        selectedScale.z -= planePositionDeltaLength;
      } else {
        selectedScale.z += planePositionDeltaLength;
      }
    }

    if (scaleMode_ == SCALE_GIZMO_MODE_ALL) {
      if (newPlanePosition.x < lastSelectionPosition_.x) {
        selectedScale.x -= planePositionDeltaLength;
        selectedScale.y -= planePositionDeltaLength;
        selectedScale.z -= planePositionDeltaLength;
      } else {
        selectedScale.x += planePositionDeltaLength;
        selectedScale.y += planePositionDeltaLength;
        selectedScale.z += planePositionDeltaLength;
      }
    }
  }

  if (scaleMode_ == SCALE_GIZMO_MODE_X) {
    scaleView_.highlightX();
  }

  if (scaleMode_ == SCALE_GIZMO_MODE_Y) {
    scaleView_.highlightY();
  }

  if (scaleMode_ == SCALE_GIZMO_MODE_Z) {
    scaleView_.highlightZ();
  }

  if (scaleMode_ == SCALE_GIZMO_MODE_ALL) {
    scaleView_.highlightAll();
  }

  lastSelectionPosition_ = newPlanePosition.vec3();
  
  Matrix4x4 selectedScaleDelta = Matrix4x4::scale(selectedScale);
  Matrix4x4 selectedNewScale = selectedNode->scale() * selectedScaleDelta;
  selectedNode->setScale(selectedNewScale);
}

bool ScaleGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  lastSelectionPosition_ = startSelectionPosition_;
  ScaleGizmoSelectionResult result = scaleView_.selectFromRay(mouseRay);
  scaleMode_ = result.mode;
  return result.selected;
}

void ScaleGizmo::mouseUp() {
  scaleMode_ = SCALE_GIZMO_MODE_UNKNOWN;
}
