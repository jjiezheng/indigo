#ifndef DEFERRED_POST_PROCESSING_PASS
#define DEFERRED_POST_PROCESSING_PASS

class CSize;
class DeferredLightingRenderStage;
class DeferredInitRenderStage;
class IViewer;

class IDeferredPostProcessingPass {

public:

  virtual void init(const CSize& screenSize) = 0;

  virtual unsigned int render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) = 0;

};

#endif