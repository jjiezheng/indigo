#ifndef DEFERRED_CLEAR_BUFFERS_PASS_H
#define DEFERRED_CLEAR_BUFFERS_PASS_H

#include "IDeferredPass.h"

class DeferredClearBuffersPass : public IDeferredPass {

public:

  DeferredClearBuffersPass(
    unsigned int colorRenderTarget, unsigned int depthRenderTarget, unsigned int lightRenderTarget, 
    unsigned int normalRenderTarget, unsigned int compositionRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , depthRenderTarget_(depthRenderTarget)
    , lightRenderTarget_(lightRenderTarget)
    , normalRenderTarget_(normalRenderTarget)
    , compositionRenderTarget_(compositionRenderTarget) { }

public:

  void init() { }

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTarget_;
  unsigned int depthRenderTarget_;
  unsigned int lightRenderTarget_;
  unsigned int normalRenderTarget_;
  unsigned int compositionRenderTarget_;

};

#endif
