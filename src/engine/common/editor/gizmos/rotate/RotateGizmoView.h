#ifndef ROTATE_GIZMO_VIEW_H
#define ROTATE_GIZMO_VIEW_H

#include "renderer/Node.h"

#include "RotateGizmoRing.h"

class IViewer;
class Ray;

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

  void highlightFromRay(const Ray& ray);

private:

  RotateGizmoRing xRing_;

  RotateGizmoRing yRing_;

  RotateGizmoRing zRing_;

};

#endif