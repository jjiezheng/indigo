#ifndef DEFERRED_COMPOSITION_PASS_H
#define DEFERRED_COMPOSITION_PASS_H

#include "IDeferredPass.h"

class IEffect;

class DeferredCompositionPass : public IDeferredPass {

public:

  DeferredCompositionPass(unsigned int finalRenderTarget, unsigned int colorMapTexture, unsigned int lightMapTexture)
    : finalRenderTarget_(finalRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , lightMapTexture_(lightMapTexture)
    , quadVbo_(0)
    , finalEffect_(0) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int finalRenderTarget_;
  unsigned int colorMapTexture_;
  unsigned int lightMapTexture_;

  unsigned int quadVbo_;
  IEffect* finalEffect_;

};

#endif
