#ifndef DEFERREDGODRAYSPASS_H_
#define DEFERREDGODRAYSPASS_H_

#include "IDeferredPostProcessingPass.h"
#include "GraphicsInterface.h"

class IEffect;

class DeferredGodRaysPass : public IDeferredPostProcessingPass {

public:

	DeferredGodRaysPass() { };

private:

  void init(const CSize& screenSize);

  unsigned int render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

  std::string passName() const;

  GraphicsInterface::TextureId passMap() const;

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  GraphicsInterface::TextureId godRaysTexture_;
  GraphicsInterface::RenderTarget godRaysRenderTarget_;

  IEffect* godRaysEffect_;

  unsigned int quadVbo_;

};

#endif