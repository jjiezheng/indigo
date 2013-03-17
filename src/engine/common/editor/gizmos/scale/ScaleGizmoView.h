#ifndef SCALE_GIZMO_VIEW_H
#define SCALE_GIZMO_VIEW_H

#include "renderer/Node.h"

#include "ScaleGizmoBox.h"

class IViewer;
class Ray;

enum ScaleGizmoMode {
  SCALE_GIZMO_MODE_UNKNOWN,
  SCALE_GIZMO_MODE_X,
  SCALE_GIZMO_MODE_Y,
  SCALE_GIZMO_MODE_Z
};

class ScaleGizmoSelectionResult {

public:

  ScaleGizmoSelectionResult()
    : selected(false)
    , mode(SCALE_GIZMO_MODE_UNKNOWN) { }

public:

  bool selected;
  ScaleGizmoMode mode;

};

class ScaleGizmoView : public Node {

public:

  ScaleGizmoView()
    : xArrow_(Color3::BLUE)
    , yArrow_(Color3::GREEN)
    , zArrow_(Color3::RED)
  { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  void highlightX();

  void highlightY();

  void highlightZ();

public:

  ScaleGizmoSelectionResult selectFromRay(const Ray& ray);

  void highlightFromRay(const Ray& ray);

private:

  ScaleGizmoBox xArrow_;
  ScaleGizmoBox yArrow_;
  ScaleGizmoBox zArrow_;

};

#endif