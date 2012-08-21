#ifndef DEFERRED_SSAO_PASS_H
#define DEFERRED_SSAO_PASS_H

#include "IDeferredPostProcessingPass.h"
#include "AverageBlur.h"
#include "GaussianBlur.h"

class DeferredInitRenderStage;
class DeferredLightingRenderStage;

class IEffect;

class DeferredSSAOPass : public IDeferredPostProcessingPass {

public:

  DeferredSSAOPass()
    : ssaoEffect_(0)
    , combineEffect_(0)
    , quadVbo_(0)
    , ssaoMapTexture_(0)
    , ssaoRenderTarget_(0)
    , noiseTexture_(0)
    , ssaoRenderTexture_(0) { }

public:

  void init(const CSize& screenSize);

   GraphicsInterface::TextureId render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

public:

  std::string passName() const;

  GraphicsInterface::TextureId passMap() const;

private:

  IEffect* ssaoEffect_;
  IEffect* combineEffect_;

  unsigned int quadVbo_;

  GraphicsInterface::TextureId ssaoMapTexture_;
  unsigned int ssaoRenderTarget_;

  GraphicsInterface::TextureId noiseTexture_;

  GraphicsInterface::TextureId ssaoRenderTexture_;

  AverageBlur blur_;

};

inline std::string DeferredSSAOPass::passName() const {
  return "SSAO";
}

inline GraphicsInterface::TextureId DeferredSSAOPass::passMap() const {
  return blur_.outputTexture();
}

#endif
