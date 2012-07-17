#ifndef DEFERRED_SSAO_PASS_H
#define DEFERRED_SSAO_PASS_H

#include "IDeferredPass.h"

class IEffect;

class DeferredSSAOPass : public IDeferredPass {

public:

  DeferredSSAOPass(unsigned int ssaoRenderTarget, unsigned int colorMapTexture, unsigned int normalMapTexture, unsigned int depthMapTexture)
    : ssaoRenderTarget_(ssaoRenderTarget)
    , colorMapTexture_(colorMapTexture)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  IEffect* ssaoEffect_;

  unsigned int quadVbo_;

  unsigned int ssaoRenderTarget_;
  unsigned int colorMapTexture_;
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  unsigned int noiseTexture_;

};

#endif
