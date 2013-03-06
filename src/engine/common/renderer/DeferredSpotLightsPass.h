#ifndef DEFERRED_SPOT_LIGHTS_PASS_H
#define DEFERRED_SPOT_LIGHTS_PASS_H

#include <vector>

#include "IDeferredLightingPass.h"
#include "core/HashMap.h"
#include "GaussianBlur.h"

class IEffect;
class Model;
class SpotLight;
class Mesh;

class DeferredSpotLightsPass : public IDeferredLightingPass {

public:

  DeferredSpotLightsPass()
    : spotLightRenderTarget_(0)
    , spotLightRenderTexture_(0)
    , quadVbo_(0)
    , lightEffectNoShadow_(0)
    , shadowDepthEffect_(0)
    , accumulationEffect_(0)
    , spotLightFrameBuffer_(0) { }

public:

  void init(const CSize& screenSize);

public:

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapFrameBuffer, const DeferredInitRenderStage& initStage);

  void collectRenderTargets(IDeferredRenderTargetContainer* renderTargetContainer);

private:

  void renderLight(SpotLight* light, IEffect* lightEffect, IViewer* viewer, unsigned int normalMap);

  void accumulateLight(SpotLight* light, unsigned int colorMap, unsigned int lightMapFrameBuffer);

  void renderShadowMap(SpotLight* light, hash_map<IEffect*, std::vector<Mesh*> >& meshes);

private:

  unsigned int spotLightRenderTarget_;
  unsigned int spotLightRenderTexture_;
  unsigned int spotLightFrameBuffer_;

  unsigned int quadVbo_;

  IEffect* lightEffectNoShadow_;
  IEffect* lightEffectShadow_;

  IEffect* shadowDepthEffect_;
  IEffect* accumulationEffect_;

  GaussianBlur depthBlur_;

};

#endif
