#ifndef DEFERRED_SSAO_PASS_H
#define DEFERRED_SSAO_PASS_H

#include "IDeferredPostProcessingPass.h"
#include "GraphicsInterface.h"
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
    , ssaoRawFrameBuffer_(0)
    , noiseTexture_(0)
    , ssaoColorBlurCombinedTexture_(0)
    , ssaoColorBlurCombinedRenderTarget_(0) { }

public:

  void init(const CSize& screenSize);

public:

  TextureId render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

public:

  std::string passName() const;

  TextureId passMap() const;

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  IEffect* ssaoEffect_;
  IEffect* combineEffect_;

  VertexBuffer quadVbo_;

  TextureId ssaoRawTexture_;
  RenderTarget ssaoRawRenderTarget_;
  FrameBuffer ssaoRawFrameBuffer_;

  TextureId noiseTexture_;

  TextureId ssaoColorBlurCombinedTexture_;
  RenderTarget ssaoColorBlurCombinedRenderTarget_;
	FrameBuffer ssaoColorBlurCombinedFrameBuffer_;

  AverageBlur blur_;

  Vector4 kernel[16];

};

inline std::string DeferredSSAOPass::passName() const {
  return "SSAO";
}

inline TextureId DeferredSSAOPass::passMap() const {
  return ssaoColorBlurCombinedRenderTarget_;
}

#endif
