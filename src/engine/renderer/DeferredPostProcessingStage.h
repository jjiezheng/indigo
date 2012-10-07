#ifndef DEFERRED_POST_PROCESSING_STAGE_H
#define DEFERRED_POST_PROCESSING_STAGE_H

#include <vector>

class IDeferredPostProcessingPass;
class DeferredLightingRenderStage;
class DeferredInitRenderStage;
class IDeferredRenderTargetContainer;

class CSize;
class IViewer;

class DeferredPostProcessingStage {

public:

  DeferredPostProcessingStage()
    : finalComposition_(0) { }

public:

  void init(const CSize& screenSize);

  void destroy();

public:

  void render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

public:

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

public:

  unsigned int finalComposition() const;

private:

  unsigned int finalComposition_;

  std::vector<IDeferredPostProcessingPass*> passes_;

};

inline unsigned int DeferredPostProcessingStage::finalComposition() const {
  return finalComposition_;
}

#endif