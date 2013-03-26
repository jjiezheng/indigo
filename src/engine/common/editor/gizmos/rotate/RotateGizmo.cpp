#include "RotateGizmo.h"

#include "../../Selection.h"

#include "renderer/IViewer.h"

#include "maths/Vector4.h"
#include "maths/Ray.h"
#include "maths/Point.h"
#include "maths/Plane.h"
#include "maths/Angles.h"
#include "maths/Matrix4x4.h"
#include "maths/Matrix3x3.h"
#include "renderer/Transforms.h"

void RotateGizmo::init() {
  isActive_ = false;
  view_ = &rotateView_;
  rotateView_.init();
}

void RotateGizmo::render(IViewer* viewer) const {
  rotateView_.render(viewer);
}

void RotateGizmo::update(float dt, const Selection& selection, const Point& mousePosition, const Ray& mouseRay, const IViewer* viewer) {
  Gizmo::update(dt, selection, mousePosition, mouseRay, viewer);
  rotateView_.highlightFromRay(mouseRay);

  if (!selection.hasSelection()) {
    isActive_ = false;
    return;
  }
  
  if (!selected_) {
    return;
  }
    
  Node* selectedNode = selection.selection();
  
  Vector4 planeNormal = Vector4::IDENTITY;
  
  Vector3 testDirection = startSelectedOrientation_.mat3x3() * Vector3::RIGHT;
  
  switch (rotateMode_) {
    case ROTATE_GIZMO_MODE_X:
      planeNormal = startSelectedOrientation_ * Vector4::RIGHT;
      testDirection = startSelectedOrientation_.mat3x3() * Vector3::FORWARD;
      break;
      
    case ROTATE_GIZMO_MODE_Y:
      planeNormal = startSelectedOrientation_ * Vector4::UP;
      testDirection = startSelectedOrientation_.mat3x3() * Vector3::RIGHT;
      break;
      
    case ROTATE_GIZMO_MODE_Z:
      planeNormal = startSelectedOrientation_ * -Vector4::FORWARD;
      testDirection = startSelectedOrientation_.mat3x3() * Vector3::RIGHT;
      break;
      
    case ROTATE_GIZMO_MODE_UNKNOWN:
      break;
  }

  Plane plane(planeNormal.x, planeNormal.y, planeNormal.z, 0.0f);
  PlaneIntersectionResult intersection = plane.testIntersection(mouseRay);

  if (intersection.intersected) {
    
    Vector3 localIntersection = intersection.position - selectedNode->translation();
    Vector3 localIntersectionDirection = localIntersection.normalize();
    
    float rotationAngle = localIntersectionDirection.angleBetween(testDirection);
    
    Vector3 testCrossLocalIntersection = testDirection.cross(localIntersectionDirection);
    
    switch (rotateMode_) {
      case ROTATE_GIZMO_MODE_X:
        rotationAngle = testCrossLocalIntersection.x >= 0 ? rotationAngle : -rotationAngle;
        break;
        
      case ROTATE_GIZMO_MODE_Y:
        rotationAngle = testCrossLocalIntersection.y >= 0 ? -rotationAngle : rotationAngle;
        break;
        
      case ROTATE_GIZMO_MODE_Z:
        rotationAngle = testCrossLocalIntersection.z >= 0 ? -rotationAngle : rotationAngle;
        break;
        
      case ROTATE_GIZMO_MODE_UNKNOWN:
        break;
    }
    
    if (lastAngle_ == 0.0f) {
      lastAngle_ = rotationAngle;
    }
    
    float angleDelta = rotationAngle - lastAngle_;

    Matrix4x4 existingOrientation = selectedNode->orientation();
    Matrix4x4 orientationIncrement = Matrix4x4::IDENTITY;

    switch (rotateMode_) {
      case ROTATE_GIZMO_MODE_X:
        orientationIncrement = Matrix4x4::rotationX(angleDelta);
        break;

      case ROTATE_GIZMO_MODE_Y:
        orientationIncrement = Matrix4x4::rotationY(-angleDelta);
        break;

      case ROTATE_GIZMO_MODE_Z:
        orientationIncrement = Matrix4x4::rotationZ(-angleDelta);
        break;

      case ROTATE_GIZMO_MODE_UNKNOWN:
        break;
    }

    Matrix4x4 newOrientation = existingOrientation * orientationIncrement;

    selectedNode->setOrientation(newOrientation);
    rotateView_.setOrientation(newOrientation);
    
    lastAngle_ = rotationAngle;
  }
}

bool RotateGizmo::mouseDown(const Point& mousePosition, const Selection& selection, const Ray& mouseRay) {
  startMousePosition_ = mousePosition;
  startSelectionPosition_ = selection.selection()->localToWorld().translation().vec3();
  lastSelectionPosition_ = startSelectionPosition_;
  lastAngle_ = 0.0f;
  
  startSelectedOrientation_ = selection.selection()->localToWorld().inverse().transpose();
  
  selected_ = true;

  RotateGizmoSelectionResult result = rotateView_.selectFromRay(mouseRay);
  rotateMode_ = result.mode;
  return result.selected;
}

void RotateGizmo::mouseUp() {
  rotateMode_ = ROTATE_GIZMO_MODE_UNKNOWN;
  selected_ = false;
  lastAngle_ = 0.0f;
}
