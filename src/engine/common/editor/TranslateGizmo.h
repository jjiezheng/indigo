#ifndef TRANSLATE_GIZMO_H
#define TRANSLATE_GIZMO_H

class Model;
class IEffect;
class IViewer;

class TranslateGizmo {

public:

  TranslateGizmo()
    : selected_(0) { }

public:

  void init();

  void render(IViewer* viewer);

public:

  void setSelected(Model* model);

private:

  Model* selected_;
  IEffect* effect_;

};

inline void TranslateGizmo::setSelected(Model* selected) {
  selected_ = selected;
}

#endif