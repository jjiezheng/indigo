#ifndef IDEFERRED_PASS_H
#define IDEFERRED_PASS_H

class IViewer;
class World;
class SceneContext;

class IDeferredPass {

public:

  virtual void init() = 0;

  virtual void render(IViewer* viewer, World& world, const SceneContext& sceneContext) = 0;

};

#endif
