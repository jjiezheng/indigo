#ifndef DEFERRED_FULL_SCREEN_BLUR_PASS
#define DEFERRED_FULL_SCREEN_BLUR_PASS

#include "IDeferredPass.h"

#include "GaussianBlur.h"

class IEffect;

class DeferredFullScreenBlurPass : public IDeferredPass {

public:

  DeferredFullScreenBlurPass(unsigned int compositionTexture, unsigned int blurRenderTarget)
    : compositionTexture_(compositionTexture)
    , blurRenderTarget_(blurRenderTarget) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int compositionTexture_;
  unsigned int blurRenderTarget_;

  unsigned int quadVbo_;

  GaussianBlur blur_;

};

#endif
