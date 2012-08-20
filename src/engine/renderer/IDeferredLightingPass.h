#ifndef IDEFERRED_LIGHTING_PASS_H
#define IDEFERRED_LIGHTING_PASS_H

class IViewer;
class World;
class SceneContext;
class DeferredInitRenderStage;
class CSize;

class IDeferredLightingPass {

public:

  virtual void init(const CSize& screenSize) = 0;

  virtual void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapTexture, const DeferredInitRenderStage& initStage) = 0;

};

#endif