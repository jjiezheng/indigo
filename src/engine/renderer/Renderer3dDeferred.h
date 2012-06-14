#ifndef RENDERER3D_DEFERRED_H
#define RENDERER3D_DEFERRED_H

#include <vector>

class World;
class SceneContext;
class IViewer;
class CSize;
class IDeferredPass;

class Renderer3dDeferred {

public:

  ~Renderer3dDeferred();

public:

  void init(const CSize& screenSize);

  void render(IViewer* viewer, World& world, const SceneContext& sceneContext);

private:

  unsigned int colorMapTexture_;
  unsigned int colorRenderTarget_;

  unsigned int normalMapTexture_;
  unsigned int normalRenderTarget_;

  unsigned int depthMapTexture_;
  unsigned int depthRenderTarget_;

  unsigned int lightMapTexture_;
  unsigned int lightRenderTarget_;

  std::vector<IDeferredPass*> passes_;
};

#endif
