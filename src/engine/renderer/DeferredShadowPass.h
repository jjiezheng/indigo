#ifndef DEFERRED_SHADOW_PASS_H
#define DEFERRED_SHADOW_PASS_H

#include "IDeferredPass.h"
#include "maths/Vector2.h"

class IEffect;

class DeferredShadowPass : public IDeferredPass {

public:

  DeferredShadowPass(unsigned int shadowRenderTarget, unsigned int colorMapTexture, unsigned int depthMapTexture)
    : shadowRenderTarget_(shadowRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , depthMapTexture_(depthMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorMapTexture_;
  unsigned int depthMapTexture_;
  unsigned int shadowRenderTarget_;

  unsigned int quadVbo_;

  IEffect* effect_;

  Vector2 halfPixel_;

};

#endif
