#ifndef DEFERRED_POST_PROCESSING_PASS
#define DEFERRED_POST_PROCESSING_PASS

#include "GraphicsInterface.h"

class CSize;
class DeferredLightingRenderStage;
class DeferredInitRenderStage;
class IViewer;

class IDeferredPostProcessingPass {

public:

  virtual void init(const CSize& screenSize) = 0;

  virtual unsigned int render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage) = 0;

public:

  virtual std::string passName() const = 0;

  virtual GraphicsInterface::TextureId passMap() const = 0;

};

#endif