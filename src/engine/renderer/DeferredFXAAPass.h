#ifndef DEFERRED_FXAA_PASS
#define DEFERRED_FXAA_PASS

#include "IDeferredPostProcessingPass.h"

class IEffect;

class DeferredFXAAPass : public IDeferredPostProcessingPass {

public:

  DeferredFXAAPass()
    : quadVbo_(0)
    , fxaaRenderTarget_(0)
    , fxaaRenderTexture_(0)
    , fxaaEffect_(0) { } 

public:

  void init(const CSize& screenSize);

  unsigned int render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

private:

  unsigned int quadVbo_;

  unsigned int fxaaRenderTarget_;
  unsigned int fxaaRenderTexture_;

  IEffect* fxaaEffect_;

};

#endif
