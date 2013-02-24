#ifndef DEFERRED_FXAA_PASS
#define DEFERRED_FXAA_PASS

#include "IDeferredPostProcessingPass.h"

class IEffect;

class DeferredFXAAPass : public IDeferredPostProcessingPass {

public:

  DeferredFXAAPass()
    : quadVbo_(0)
    , colorLumaTarget_(0)
    , colorLumaTexture_(0)
    , fxaaRenderTarget_(0)
    , fxaaRenderTexture_(0)
    , colorLumaEffect_(0)
    , fxaaEffect_(0) { } 

public:

  void init(const CSize& screenSize);

  void destroy();

public:

  TextureId render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

public:

  std::string passName() const;

  TextureId passMap() const;

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  VertexBuffer quadVbo_;

  RenderTarget colorLumaTarget_;
  TextureId colorLumaTexture_;

  RenderTarget fxaaRenderTarget_;
  TextureId fxaaRenderTexture_;

  IEffect* colorLumaEffect_;
  IEffect* fxaaEffect_;

};

inline std::string DeferredFXAAPass::passName() const {
  return "FXAA";
}

inline TextureId DeferredFXAAPass::passMap() const {
  return fxaaRenderTexture_;
}

#endif
