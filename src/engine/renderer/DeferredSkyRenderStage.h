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

  void init(const CSize &screenSize);

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