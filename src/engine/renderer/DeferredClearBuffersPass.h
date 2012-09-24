#ifndef DEFERRED_CLEAR_BUFFERS_PASS_H
#define DEFERRED_CLEAR_BUFFERS_PASS_H

#include "IDeferredPass.h"

class DeferredClearBuffersPass : public IDeferredPass {

public:

  DeferredClearBuffersPass(
    unsigned int colorRenderTarget, unsigned int depthRenderTarget, unsigned int normalRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , depthRenderTarget_(depthRenderTarget)
    , normalRenderTarget_(normalRenderTarget) { }

public:

  void init(const CSize& screenSize) { }

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTarget_;
  unsigned int depthRenderTarget_;
  unsigned int normalRenderTarget_;

};

#endif
