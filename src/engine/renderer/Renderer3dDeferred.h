#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

#include <vector>

#include "memory/STLAllocators.h"
#include "services/IRenderChannelInfoService.h"

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

class IEffect;

class Renderer3dDeferred : public IDeferredRenderTargetContainer, public IRenderChannelInfoService {

public:

  static Renderer3dDeferred* renderer();

public:

  explicit
  Renderer3dDeferred(ScopeStack* systemStack)
    : activeRenderTargetIndex_(0)
    , initStage_(systemStack)
    , presentStage_(systemStack)
    , renderTargets_(vec_alloc<DeferredRenderTarget>(systemStack)){ };

public:

  void init(const CSize& screenSize);

  void destroy();

public:

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

public:

  void addRenderTarget(const std::string& renderTargetName, unsigned int renderTargetId);

public:

  void presentRenderTarget(unsigned int renderTargetIndex);

public:

	std::string getActiveRenderChannel() const;

private:

  DeferredInitRenderStage initStage_;
  DeferredLightingRenderStage lightingStage_;
  DeferredSkyRenderStage skyStage_;
  DeferredPostProcessingStage postProcessingStage_;
  DeferredPresentStage presentStage_;

private:

  std::vector<DeferredRenderTarget, vec_alloc<DeferredRenderTarget> > renderTargets_;
  unsigned int activeRenderTargetIndex_;

private:

  IEffect* effect_;
  unsigned int screenPlaneId_;

};

#endif
