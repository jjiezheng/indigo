#ifndef DEFERRED_POST_PROCESSING_STAGE_H
#define DEFERRED_POST_PROCESSING_STAGE_H

#include "memory/Pools.h"

class IDeferredPostProcessingPass;
class DeferredLightingRenderStage;
class DeferredInitRenderStage;
class IDeferredRenderTargetContainer;
class SceneContext;

class CSize;
class IViewer;

class DeferredPostProcessingStage {

public:

  DeferredPostProcessingStage()
    : finalComposition_(0) { }

public:

  void init(const CSize& screenSize);

public:

  void render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

public:

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

public:

  unsigned int finalComposition() const;

private:

  unsigned int finalComposition_;

  syspool::vector<IDeferredPostProcessingPass*>::type passes_;

};

inline unsigned int DeferredPostProcessingStage::finalComposition() const {
  return finalComposition_;
}

#endif