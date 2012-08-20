#ifndef DEFERRED_INIT_RENDER_STAGE_H
#define DEFERRED_INIT_RENDER_STAGE_H

#include "IDeferredRenderStage.h"

class IDeferredPass;

class DeferredInitRenderStage : public IDeferredRenderStage {

public:

  void init(const CSize &screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

public:

  unsigned int depthMap() const;

  unsigned int normalMap() const;

  unsigned int colorMap() const;

private:

  unsigned int colorMapTexture_;
  unsigned int colorRenderTarget_;

  unsigned int normalMapTexture_;
  unsigned int normalRenderTarget_;

  unsigned int depthMapTexture_;
  unsigned int depthRenderTarget_;

  std::vector<IDeferredPass*> passes_;

};

inline unsigned int DeferredInitRenderStage::depthMap() const {
  return depthMapTexture_;
}

inline unsigned int DeferredInitRenderStage::normalMap() const {
  return normalMapTexture_;
}

inline unsigned int DeferredInitRenderStage::colorMap() const {
  return colorMapTexture_;
}


#endif