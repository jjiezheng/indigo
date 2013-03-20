#ifndef ROTATE_GIZMO_VIEW_H
#define ROTATE_GIZMO_VIEW_H

#include "renderer/Node.h"

#include "RotateGizmoRing.h"

class IViewer;
class Ray;

enum RotateGizmoMode {
  ROTATE_GIZMO_MODE_UNKNOWN,
  ROTATE_GIZMO_MODE_X,
  ROTATE_GIZMO_MODE_Y,
  ROTATE_GIZMO_MODE_Z
};

class RotateGizmoSelectionResult {

public:

  RotateGizmoSelectionResult()
    : selected(false)
    , mode(ROTATE_GIZMO_MODE_UNKNOWN) { }

public:

  bool selected;
  RotateGizmoMode mode;

};

class RotateGizmoView : public Node {

public:

  RotateGizmoView() 
    : xRing_(Color3::BLUE)
    , yRing_(Color3::GREEN)
    , zRing_(Color3::RED)
  {

  }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  void highlightX();

  void highlightY();

  void highlightZ();

public:

  RotateGizmoSelectionResult selectFromRay(const Ray& ray);

  void highlightFromRay(const Ray& ray);

private:

  RotateGizmoRing xRing_;
  RotateGizmoRing yRing_;
  RotateGizmoRing zRing_;

};

#endif