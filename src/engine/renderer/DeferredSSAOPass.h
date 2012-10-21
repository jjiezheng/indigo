#ifndef DEFERRED_SSAO_PASS_H
#define DEFERRED_SSAO_PASS_H

#include "IDeferredPostProcessingPass.h"
#include "AverageBlur.h"
#include "GaussianBlur.h"

#include "maths/Vector4.h"

class DeferredInitRenderStage;
class DeferredLightingRenderStage;

class IEffect;

class DeferredSSAOPass : public IDeferredPostProcessingPass {

public:

  DeferredSSAOPass()
    : ssaoEffect_(0)
    , combineEffect_(0)
    , quadVbo_(0)
    , ssaoRawTexture_(0)
    , ssaoRawRenderTarget_(0)
    , noiseTexture_(0)
    , ssaoColorBlurCombinedTexture_(0)
    , ssaoColorBlurCombinedRenderTarget_(0) { }

public:

  void init(const CSize& screenSize);

public:

   GraphicsInterface::TextureId render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

public:

  std::string passName() const;

  GraphicsInterface::TextureId passMap() const;

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  IEffect* ssaoEffect_;
  IEffect* combineEffect_;

  unsigned int quadVbo_;

  GraphicsInterface::TextureId ssaoRawTexture_;
  GraphicsInterface::RenderTarget ssaoRawRenderTarget_;
  
  GraphicsInterface::TextureId noiseTexture_;
  
  GraphicsInterface::TextureId ssaoColorBlurCombinedTexture_;
  GraphicsInterface::RenderTarget ssaoColorBlurCombinedRenderTarget_;

  AverageBlur blur_;

  Vector4 kernel[16];

};

inline std::string DeferredSSAOPass::passName() const {
  return "SSAO";
}

inline GraphicsInterface::TextureId DeferredSSAOPass::passMap() const {
  return ssaoColorBlurCombinedRenderTarget_;
}

#endif
