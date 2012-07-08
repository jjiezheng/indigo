#ifndef DEFERRED_FXAA_PASS
#define DEFERRED_FXAA_PASS

#include "IDeferredPass.h"

class IEffect;

class DeferredFXAAPass : public IDeferredPass {

public:

  DeferredFXAAPass(unsigned int fxaaRenderTarget, unsigned int compositionRenderTexture) 
    : fxaaRenderTarget_(fxaaRenderTarget) 
    , compositionRenderTexture_(compositionRenderTexture) { } 

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int quadVbo_;
  unsigned int fxaaRenderTarget_;
  unsigned int compositionRenderTexture_;

  IEffect* fxaaEffect_;

};

#endif
