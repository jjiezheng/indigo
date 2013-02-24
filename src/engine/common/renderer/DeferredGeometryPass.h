#ifndef DEFERRED_GEOMETRY_PASS_H
#define DEFERRED_GEOMETRY_PASS_H

#include "GraphicsInterface.h"
#include "IDeferredPass.h"

class DeferredGeometryPass : public IDeferredPass {
  
public:
  
  virtual ~DeferredGeometryPass() { };

public:

  DeferredGeometryPass(RenderTarget colorRenderTarget, RenderTarget normalRenderTarget, RenderTarget depthRenderTarget)
    : colorRenderTarget_(colorRenderTarget)
    , normalRenderTarget_(normalRenderTarget)
    , depthRenderTarget_(depthRenderTarget)
    , gBufferFrameBuffer_(0) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  RenderTarget colorRenderTarget_;
  RenderTarget normalRenderTarget_;
  RenderTarget depthRenderTarget_;

  FrameBuffer gBufferFrameBuffer_;
};

#endif
