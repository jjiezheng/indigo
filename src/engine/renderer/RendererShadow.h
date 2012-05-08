#ifndef RENDERER_SHADOW_H
#define RENDERER_SHADOW_H

#include "Shader.h"

class Camera;
class World;
class SceneContext;
class Renderer3d;

class Vector2;

class RendererShadow {
  
public:
  
  void init(const Vector2& screenSize);
  
  void render(const World& world, SceneContext& sceneContext);
  
  void renderDebug(SceneContext& sceneContext);
  
private:
  
  GLuint frameBuffer_;
  GLuint depthBuffer_;
  GLuint shadowTexture_;
  
  GLuint debugVertArray_;
  GLuint debugVertBuffer_;
  GLuint debugUVBuffer_;
  Shader debugShader_;
};

#endif
