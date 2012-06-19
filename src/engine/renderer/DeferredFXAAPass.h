#ifndef DEFERRED_FXAA_PASS
#define DEFERRED_FXAA_PASS

#include "IDeferredPass.h"
#include "maths/Vector2.h"

class IEffect;

class DeferredFXAAPass : public IDeferredPass {

public:

  DeferredFXAAPass(unsigned int finalRenderTexture, const Vector2& halfPixel) 
    : finalRenderTexture_(finalRenderTexture)
    , halfPixel_(halfPixel) { } 

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int quadVbo_;
  unsigned int finalRenderTexture_;

  IEffect* finalEffect_;
  Vector2 halfPixel_;

};

#endif
