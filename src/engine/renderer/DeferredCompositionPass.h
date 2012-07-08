#ifndef DEFERRED_COMPOSITION_PASS_H
#define DEFERRED_COMPOSITION_PASS_H

#include "IDeferredPass.h"

class IEffect;

class DeferredCompositionPass : public IDeferredPass {

public:

  DeferredCompositionPass(unsigned int finalRenderTarget, unsigned int colorMapTexture, unsigned int lightMapTexture)
    : finalRenderTarget_(finalRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , lightMapTexture_(lightMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  IEffect* finalEffect_;
  unsigned int quadVbo_;

  unsigned int finalRenderTarget_;
  unsigned int colorMapTexture_;
  unsigned int lightMapTexture_;

};

#endif
