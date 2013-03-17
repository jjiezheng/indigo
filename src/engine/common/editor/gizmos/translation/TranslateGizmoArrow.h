#ifndef TRANSLATE_GIZMO_ARROW_H
#define TRANSLATE_GIZMO_ARROW_H

#include "renderer/Node.h"
#include "renderer/Model.h"

class IEffect;
class IViewer;

class TranslateGizmoArrow : public Node {

public:

  TranslateGizmoArrow(const Color3& arrowColor)
    : arrowColor_(arrowColor)
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

  Model coneModel_;
  Model lineModel_;
  Color3 arrowColor_;
  bool isHighlighted_;
  bool drawBounds_;

};

inline void TranslateGizmoArrow::setHighlight(bool isHighlighted) {
  isHighlighted_ = isHighlighted;
}

#endif