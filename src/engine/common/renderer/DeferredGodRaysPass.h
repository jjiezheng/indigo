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

  TextureId render(IViewer* viewer, unsigned int inputMap, const SceneContext& sceneContext, const DeferredInitRenderStage& initStage);

  std::string passName() const;

  TextureId passMap() const;

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  TextureId godRaysTexture_;
  RenderTarget godRaysRenderTarget_;

  IEffect* godRaysEffect_;

  unsigned int quadVbo_;

};

#endif