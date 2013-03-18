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
  SCALE_GIZMO_MODE_Z,
  SCALE_GIZMO_MODE_ALL
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
    : xBox_(Color3::BLUE, true)
    , yBox_(Color3::GREEN, true)
    , zBox_(Color3::RED, true)
    , allBox_(Color3::GREY, false)
  { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  void highlightX();

  void highlightY();

  void highlightZ();

  void highlightAll();

public:

  ScaleGizmoSelectionResult selectFromRay(const Ray& ray);

  void highlightFromRay(const Ray& ray);

private:

  ScaleGizmoBox xBox_;
  ScaleGizmoBox yBox_;
  ScaleGizmoBox zBox_;
  ScaleGizmoBox allBox_;

};

#endif