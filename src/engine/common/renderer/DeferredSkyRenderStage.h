#ifndef DEFERRED_SKYRENDER_STAGE_H
#define DEFERRED_SKYRENDER_STAGE_H

#include "GraphicsInterface.h"
#include "IDeferredRenderStage.h"

class IDeferredRenderTargetContainer;
class IEffect;
class IViewer;

class World;
class SceneContext;
class CSize;

class DeferredLightingRenderStage;

class DeferredSkyRenderStage : public IDeferredRenderStage {

public:

  DeferredSkyRenderStage()
    : skyRenderTarget_(0)
    , skyRenderTexture_(0)
    , skyMapTexture_(0)
    , quadVBO_(0)
    , compositeEffect_(0) { }


public:

  void init(const CSize &screenSize);

  void destroy() { };

public:

  void render(IViewer* viewer, World& world, DeferredLightingRenderStage& lightingStage);

public:

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  GraphicsInterface::RenderTarget skyRenderTarget_;
  GraphicsInterface::TextureId skyRenderTexture_;
  GraphicsInterface::TextureId skyMapTexture_;

  GraphicsInterface::VertexBuffer quadVBO_;

  IEffect* compositeEffect_;

};

#endif