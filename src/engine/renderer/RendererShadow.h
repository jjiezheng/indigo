#ifndef RENDERER_SHADOW_H
#define RENDERER_SHADOW_H

class Camera;
class World;
class SceneContext;
class Renderer3d;

class Vector2;

class RendererShadow {
  
public:
  
  void init(const Vector2& screenSize);
  
  void render(const World& world, SceneContext& sceneContext);
  
private:
  
  GLuint frameBuffer_;
  GLuint depthBuffer_;
  GLuint shadowTexture_;
};

#endif
