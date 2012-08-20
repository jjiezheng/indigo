#ifndef DEFERRED_SSAO_PASS_H
#define DEFERRED_SSAO_PASS_H

#include "IDeferredPostProcessingPass.h"
#include "AverageBlur.h"
#include "GaussianBlur.h"

class DeferredInitRenderStage;
class DeferredLightingRenderStage;

class IEffect;

class DeferredSSAOPass : public IDeferredPostProcessingPass {

public:

  DeferredSSAOPass() { }

public:

  void init(const CSize& screenSize);

  unsigned int render(IViewer* viewer, unsigned int inputMap, const DeferredInitRenderStage& initStage);

private:

  IEffect* ssaoEffect_;
  IEffect* combineEffect_;

  unsigned int quadVbo_;

  unsigned int ssaoMapTexture_;
  unsigned int ssaoRenderTarget_;

  unsigned int noiseTexture_;

  unsigned int ssaoRenderTexture_;

  AverageBlur blur_;

};

#endif
