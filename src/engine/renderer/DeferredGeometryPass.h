#ifndef DEFERRED_GEOMETRY_PASS_H
#define DEFERRED_GEOMETRY_PASS_H

#include "IDeferredPass.h"

class DeferredGeometryPass : public IDeferredPass {

public:

  DeferredGeometryPass(unsigned int colorRenderTarget, unsigned int normalRenderTarget, unsigned int depthRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , normalRenderTarget_(normalRenderTarget)
    , depthRenderTarget_(depthRenderTarget) { }

public:

  void init() { };

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTarget_;
  unsigned int normalRenderTarget_;
  unsigned int depthRenderTarget_;

};

#endif
