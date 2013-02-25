#ifndef DEFERRED_INIT_RENDER_STAGE_H
#define DEFERRED_INIT_RENDER_STAGE_H

#include <vector>
#include "IDeferredRenderStage.h"

#include "GraphicsInterface.h"

class IDeferredPass;
class IDeferredRenderTargetContainer;

class DeferredInitRenderStage : public IDeferredRenderStage {

public:

  DeferredInitRenderStage()
    : colorMapTexture_(0)
    , colorRenderTarget_(0)
    , normalMapTexture_(0)
    , normalRenderTarget_(0)
    , normalViewSpaceMapTexture_(0)
    , normalViewSpaceRenderTarget_(0)
    , depthMapTexture_(0)
    , depthRenderTarget_(0) { }

public:

  void init(const CSize &screenSize);

  void destroy() { };

public:

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

public:

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

public:

  TextureId colorMap() const;

  TextureId normalMap() const;

  TextureId normalViewSpaceMap() const;

  TextureId depthMap() const;

private:

  TextureId colorMapTexture_;
  RenderTarget colorRenderTarget_;

  TextureId normalMapTexture_;
  RenderTarget normalRenderTarget_;

  TextureId normalViewSpaceMapTexture_;
  RenderTarget normalViewSpaceRenderTarget_;

  TextureId depthMapTexture_;
  RenderTarget depthRenderTarget_;

  std::vector<IDeferredPass*> passes_;

};

inline TextureId DeferredInitRenderStage::colorMap() const {
  return colorMapTexture_;
}

inline TextureId DeferredInitRenderStage::normalMap() const {
  return normalMapTexture_;
}

inline TextureId DeferredInitRenderStage::normalViewSpaceMap() const {
  return normalViewSpaceMapTexture_;
}

inline TextureId DeferredInitRenderStage::depthMap() const {
  return depthMapTexture_;
}

#endif