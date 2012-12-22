#ifndef DEFERRED_POINT_LIGHTS_PASS_H
#define DEFERRED_POINT_LIGHTS_PASS_H

#include "IDeferredPass.h"

class IEffect;
class Model;

class DeferredPointLightsPass : public IDeferredPass {
  
public:
  
  virtual ~DeferredPointLightsPass() { };

public:

  DeferredPointLightsPass(unsigned int lightMapRenderTarget, unsigned int normalMapTexture, unsigned int depthMapTexture)
    : lightMapRenderTarget_(lightMapRenderTarget)
    , normalMapTexture_(normalMapTexture)
    , depthMapTexture_(depthMapTexture)
    , quadVbo_(0)
    , pointLightEffect_(0)
    , pointLightModel_(0) { }

public:

  void init();

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int lightMapRenderTarget_;
  unsigned int normalMapTexture_;
  unsigned int depthMapTexture_;

  unsigned int quadVbo_;

  IEffect* pointLightEffect_;
  Model* pointLightModel_;

};

#endif
