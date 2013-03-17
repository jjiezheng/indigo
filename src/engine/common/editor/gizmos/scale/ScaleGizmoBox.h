#ifndef SCALE_GIZMO_BOX_H
#define SCALE_GIZMO_BOX_H

#include "renderer/Node.h"
#include "renderer/Model.h"

class IEffect;
class IViewer;

class ScaleGizmoBox : public Node {

public:

  ScaleGizmoBox(const Color3& boxColor)
    : boxColor_(boxColor)
    , isHighlighted_(false)
    , drawBounds_(false) { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  void setHighlight(bool isHighlighted);

private:

  IEffect* effect_;

private:

  Model boxModel_;
  Model lineModel_;
  Color3 boxColor_;
  bool isHighlighted_;
  bool drawBounds_;

};

inline void ScaleGizmoBox::setHighlight(bool isHighlighted) {
  isHighlighted_ = isHighlighted;
}

#endif