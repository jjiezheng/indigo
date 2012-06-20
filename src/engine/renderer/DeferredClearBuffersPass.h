#ifndef DEFERRED_CLEAR_BUFFERS_PASS_H
#define DEFERRED_CLEAR_BUFFERS_PASS_H

#include "IDeferredPass.h"

class DeferredClearBuffersPass : public IDeferredPass {

public:

  DeferredClearBuffersPass(
    unsigned int colorRenderTarget, unsigned int depthRenderTarget, unsigned int lightRenderTarget, 
    unsigned int normalRenderTarget, unsigned int shadowMapTarget, unsigned int finalRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , depthRenderTarget_(depthRenderTarget)
    , lightRenderTarget_(lightRenderTarget)
    , normalRenderTarget_(normalRenderTarget)
    , shadowMapTarget_(shadowMapTarget)
    , finalRenderTarget_(finalRenderTarget) { }

public:

  void init() { }

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTarget_;
  unsigned int depthRenderTarget_;
  unsigned int lightRenderTarget_;
  unsigned int normalRenderTarget_;
  unsigned int shadowMapTarget_;
  unsigned int finalRenderTarget_;

};

#endif
