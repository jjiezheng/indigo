#ifndef DEFERRED_PRESENT_PASS
#define DEFERRED_PRESENT_PASS

#include "IDeferredPass.h"

#include "GaussianBlur.h"

class IEffect;

class DeferredPresentPass : public IDeferredPass {

public:

  DeferredPresentPass(unsigned int fullScreenTexture)
    : fullScreenTexture_(fullScreenTexture)
    , quadVbo_(0)
    , effect_(0) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int fullScreenTexture_;

  unsigned int quadVbo_;

  IEffect* effect_;

};

#endif
