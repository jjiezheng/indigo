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

  void selectFromRay(const Ray& ray, const World& world);

private:

  IEffect* selectionEffect_;

  Model* selected_;

};

#endif
