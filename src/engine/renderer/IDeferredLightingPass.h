#ifndef IDEFERRED_LIGHTING_PASS_H
#define IDEFERRED_LIGHTING_PASS_H

class IViewer;
class World;
class SceneContext;
class DeferredInitRenderStage;
class CSize;
class IDeferredRenderTargetContainer;

class IDeferredLightingPass {

public:

  virtual ~IDeferredLightingPass() { };

public:

  virtual void init(const CSize& screenSize) = 0;

public:

  virtual void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapTexture, const DeferredInitRenderStage& initStage) = 0;

  virtual void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) = 0;

};

#endif