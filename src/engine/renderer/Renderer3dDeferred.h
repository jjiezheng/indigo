#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

#include <vector>

class World;
class SceneContext;
class IViewer;
class CSize;
class IDeferredPass;
class IDeferredRenderStage;

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"
#include "DeferredPostProcessingStage.h"
#include "DeferredPresentStage.h"

class Renderer3dDeferred {

public:

  static Renderer3dDeferred* renderer();

public:

  Renderer3dDeferred() { };

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  DeferredInitRenderStage initStage_;
  DeferredLightingRenderStage lightingStage_;
  DeferredPostProcessingStage postProcessingStage_;
  DeferredPresentStage presentStage_;
};

#endif
