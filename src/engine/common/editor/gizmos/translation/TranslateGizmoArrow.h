#ifndef TRANSLATE_GIZMO_ARROW_H
#define TRANSLATE_GIZMO_ARROW_H

#include "renderer/Node.h"
#include "renderer/Model.h"

class IEffect;
class IViewer;

class TranslateGizmoArrow : public Node {

public:

  TranslateGizmoArrow(const Color3& arrowColor)
    : arrowColor_(arrowColor) { }

public:

  void init();

  void render(IViewer* viewer);

private:

  IEffect* effect_;

private:

  Model coneModel_;
  Model lineModel_;
  Color3 arrowColor_;

};

#endif