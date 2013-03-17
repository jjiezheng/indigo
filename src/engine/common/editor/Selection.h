#ifndef SELECTION_H
#define SELECTION_H

class Ray;
class World;
class IEffect;
class IViewer;
class Model;

class Selection {

public:

  Selection()
    : selected_(0) { }

public:

  void init();

  void render(IViewer* viewer);

  void select(const Ray& mouseRay, const World& world);

public:

  bool hasSelection() const;

  Model* selection() const;

private:

  IEffect* selectionEffect_;

  Model* selected_;

};

inline bool Selection::hasSelection() const {
  return selected_ != 0;
}

inline Model* Selection::selection() const {
  return selected_;
}

#endif
