#ifndef DEFERRED_GEOMETRY_PASS_H
#define DEFERRED_GEOMETRY_PASS_H

#include "IDeferredPass.h"

class DeferredGeometryPass : public IDeferredPass {

public:

  DeferredGeometryPass(unsigned int colorRenderTarget, unsigned int normalRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , normalRenderTarget_(normalRenderTarget) { }

public:

  void init(const CSize& screenSize) { };

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorRenderTarget_;
  unsigned int normalRenderTarget_;

};

#endif
