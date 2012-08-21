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

  GraphicsInterface::TextureId render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

public:

  std::string passName() const;

  GraphicsInterface::TextureId passMap() const;

private:

  unsigned int quadVbo_;

  unsigned int fxaaRenderTarget_;
  GraphicsInterface::TextureId fxaaRenderTexture_;

  IEffect* fxaaEffect_;

};

inline std::string DeferredFXAAPass::passName() const {
  return "FXAA";
}

inline GraphicsInterface::TextureId DeferredFXAAPass::passMap() const {
  return fxaaRenderTexture_;
}

#endif
