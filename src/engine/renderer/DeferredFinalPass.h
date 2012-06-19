#ifndef DEFERRED_FINAL_PASS_H
#define DEFERRED_FINAL_PASS_H

#include "maths/Vector2.h"

#include "IDeferredPass.h"

class IEffect;

class DeferredFinalPass : public IDeferredPass {

public:

  DeferredFinalPass(unsigned int finalRenderTarget, unsigned int colorMapTexture, unsigned int lightMapTexture, const Vector2& halfPixel)
    : finalRenderTarget_(finalRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , lightMapTexture_(lightMapTexture)
    , halfPixel_(halfPixel) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  IEffect* finalEffect_;
  unsigned int quadVbo_;

  unsigned int finalRenderTarget_;
  unsigned int colorMapTexture_;
  unsigned int lightMapTexture_;

  Vector2 halfPixel_;

};

#endif
