#ifndef DEFERRED_INIT_RENDER_STAGE_H
#define DEFERRED_INIT_RENDER_STAGE_H

#include <vector>

#include "memory/STLAllocators.h"
#include "memory/ScopeStack.h"

#include "IDeferredRenderStage.h"

class IDeferredPass;
class IDeferredRenderTargetContainer;

class DeferredInitRenderStage : public IDeferredRenderStage {

public:

  DeferredInitRenderStage(ScopeStack* systemStack)
    : colorMapTexture_(0)
    , colorRenderTarget_(0)
    , normalMapTexture_(0)
    , normalRenderTarget_(0)
    , systemStack_(systemStack)
    , passes_(vec_alloc<IDeferredPass*>(systemStack)) { }

public:

  void init(const CSize &screenSize);

  void destroy() { };

public:

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

public:

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

public:

  unsigned int depthMap() const;

  unsigned int normalMap() const;

  unsigned int colorMap() const;

private:
  
  unsigned int colorMapTexture_;
  unsigned int colorRenderTarget_;

  unsigned int normalMapTexture_;
  unsigned int normalRenderTarget_;

  ScopeStack* systemStack_;
  std::vector<IDeferredPass*, vec_alloc<IDeferredPass*>> passes_;

};

inline unsigned int DeferredInitRenderStage::normalMap() const {
  return normalMapTexture_;
}

inline unsigned int DeferredInitRenderStage::colorMap() const {
  return colorMapTexture_;
}


#endif