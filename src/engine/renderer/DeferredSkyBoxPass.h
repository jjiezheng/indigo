#ifndef DEFERRED_SKYBOX_PASS_H
#define DEFERRED_SKYBOX_PASS_H

#include "IDeferredLightingPass.h"

class DeferredSkyBoxPass : public IDeferredLightingPass {

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapTexture, const DeferredInitRenderStage& initStage);

private:

  unsigned int skyBoxMesh_;

}; 

#endif
