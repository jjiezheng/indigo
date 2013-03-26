#ifndef ROTATE_GIZMO_RING_H
#define ROTATE_GIZMO_RING_H

#include "renderer/Model.h"
#include "renderer/GraphicsInterface.h"
#include "renderer/Color3.h"

class IViewer;

class RotateGizmoRing : public Node {

public:

  RotateGizmoRing(const Color3& ringColor)
    : effect_(0)
    , ringColor_(ringColor) 
    , isHighlighted_(false)
    , drawBounds_(false)
  { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  void setHighlight(bool isHighlighted);

  BoundingBox boundingBox() const;

private:

  VertexBuffer lineBuffer_;
  IEffect* effect_;
  Color3 ringColor_;
  Model circleModel_;
  bool isHighlighted_;
  bool drawBounds_;

};

inline void RotateGizmoRing::setHighlight(bool isHighlighted) {
  isHighlighted_ = isHighlighted;
}

#endif