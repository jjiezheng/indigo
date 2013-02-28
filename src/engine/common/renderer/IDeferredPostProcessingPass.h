#ifndef DEFERRED_POST_PROCESSING_PASS
#define DEFERRED_POST_PROCESSING_PASS

#include "GraphicsInterface.h"

class CSize;
class DeferredInitRenderStage;
class IViewer;
class IDeferredRenderTargetContainer;
class SceneContext;

class IDeferredPostProcessingPass {

public:

  virtual ~IDeferredPostProcessingPass() { };

public:

  virtual void init(const CSize& screenSize) = 0;

public:

  virtual unsigned int render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage) = 0;

public:

  virtual std::string passName() const = 0;

  virtual TextureId passMap() const = 0;

  virtual void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer) = 0;

};

#endif