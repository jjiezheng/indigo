#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

#include <vector>

#include "IDeferredRenderTargetContainer.h"

#include "DeferredInitRenderStage.h"
#include "DeferredLightingRenderStage.h"
#include "DeferredSkyRenderStage.h"
#include "DeferredPostProcessingStage.h"
#include "DeferredPresentStage.h"
#include "DeferredRenderTarget.h"

class World;
class SceneContext;
class IViewer;
class CSize;
class IDeferredPass;
class IDeferredRenderStage;

class Renderer3dDeferred : public IDeferredRenderTargetContainer {

public:

  static Renderer3dDeferred* renderer();

public:

  Renderer3dDeferred() { };

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

public:

  void addRenderTarget(const std::string& renderTargetName, unsigned int renderTargetId);

public:

  void presentRenderTarget(unsigned int renderTargetIndex);

private:

  DeferredInitRenderStage initStage_;
  DeferredLightingRenderStage lightingStage_;
  DeferredSkyRenderStage skyStage_;
  DeferredPostProcessingStage postProcessingStage_;
  DeferredPresentStage presentStage_;

private:

  std::vector<DeferredRenderTarget> renderTargets_;
  unsigned int activeRenderTargetIndex_;

};

#endif
