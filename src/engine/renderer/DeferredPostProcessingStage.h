#ifndef DEFERRED_POST_PROCESSING_STAGE_H
#define DEFERRED_POST_PROCESSING_STAGE_H

#include <vector>

class IDeferredPostProcessingPass;
class DeferredLightingRenderStage;
class DeferredInitRenderStage;

class CSize;
class IViewer;

class DeferredPostProcessingStage {

public:

  DeferredPostProcessingStage()
    : finalComposition_(0) { }

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

  unsigned int finalComposition() const;

private:

  std::vector<IDeferredPostProcessingPass*> passes_;

  unsigned int finalComposition_;

};

inline unsigned int DeferredPostProcessingStage::finalComposition() const {
  return finalComposition_;
}

#endif