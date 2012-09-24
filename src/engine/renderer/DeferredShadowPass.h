#ifndef DEFERRED_SHADOW_PASS_H
#define DEFERRED_SHADOW_PASS_H

#include "IDeferredPass.h"
#include "maths/Vector2.h"

class IEffect;

class DeferredShadowPass : public IDeferredPass {

public:

  DeferredShadowPass(unsigned int shadowMapTexture, unsigned int shadowRenderTarget, unsigned int lightRenderTarget, unsigned int depthMapTexture, const Vector2& halfPixel)
    : shadowMapTexture_(shadowMapTexture)
    , shadowRenderTarget_(shadowRenderTarget)
    , depthMapTexture_(depthMapTexture)
    , lightRenderTarget_(lightRenderTarget)
    , halfPixel_(halfPixel) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightRenderTarget_;

  unsigned int shadowMapTexture_;
  unsigned int shadowRenderTarget_;
  unsigned int depthMapTexture_;

  unsigned int quadVbo_;

  IEffect* shadowLightEffect_;
  IEffect* shadowMapEffect_;

  Vector2 halfPixel_;

};

#endif
