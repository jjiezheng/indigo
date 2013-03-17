#ifndef TRANSLATE_GIZMO_VIEW_H
#define TRANSLATE_GIZMO_VIEW_H

#include "renderer/Color3.h"

#include "TranslateGizmoArrow.h"

class IViewer;
class Ray;

enum TranslateGizmoMode {
  TRANSLATE_GIZMO_MODE_UNKNOWN,
  TRANSLATE_GIZMO_MODE_X,
  TRANSLATE_GIZMO_MODE_Y,
  TRANSLATE_GIZMO_MODE_Z
};

class TranslateGizmoSelectionResult {

public:

  TranslateGizmoSelectionResult()
    : selected(false)
    , mode(TRANSLATE_GIZMO_MODE_UNKNOWN) { }

public:

  bool selected;
  TranslateGizmoMode mode;

};

class TranslateGizmoView : public Node {

public:

  TranslateGizmoView()
    : xArrow_(Color3::BLUE)
    , yArrow_(Color3::GREEN)
    , zArrow_(Color3::RED)
  { }

public:

  void init();

  void render(IViewer* viewer) const;

public:

  TranslateGizmoSelectionResult selectFromRay(const Ray& ray);

  void highlightFromRay(const Ray& ray);

private:

  TranslateGizmoArrow xArrow_;
  TranslateGizmoArrow yArrow_;
  TranslateGizmoArrow zArrow_;

};

#endif