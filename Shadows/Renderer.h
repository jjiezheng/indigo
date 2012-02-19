#ifndef Renderer_H_
#define Renderer_H_

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include <vector>

class SceneNode;
class Light;
class Model;
class Shader;
class Camera;

class Renderer {
  
public:
  
  static Renderer* renderer();
  
private:
  
  Renderer() = default;

public:
  
  void init();
  
  void render(SceneNode* sceneNode);
  
private:
  
  void renderScene(Shader* shader);
  
  void renderUI();
  void render3d();
  
public:
  
  void queueLight(Light* light);
  
  void queueShadowLight(Light* light);
  
  void queueModel(Model* model);
  
  void queueCamera(Camera* camera);
  
  void queueUI(SceneNode* node);
  
private:
  
  std::vector<Camera*> cameras_;
  std::vector<Light*> lights_;
  std::vector<Light*> shadowLights_;
  std::vector<Model*> models_;
  std::vector<SceneNode*> uiNodes_;
  
private:
  
  GLuint shadowFrameBuffer_;
  GLuint shadowRenderDepthBuffer_;
  GLuint shadowRenderColorBuffer_;
  GLuint shadowTexture_;

  GLuint depthDebugVertArray_;
  GLuint depthDebugVertBuffer_;
  GLuint depthDebugUVBuffer_;

};

inline
void Renderer::queueCamera(Camera* camera) {
  cameras_.push_back(camera);
}

inline
void Renderer::queueLight(Light* light) {
  lights_.push_back(light);
}

inline
void Renderer::queueModel(Model *model) {
  models_.push_back(model);
}

inline
void Renderer::queueShadowLight(Light* light) {
  shadowLights_.push_back(light);
}

inline
void Renderer::queueUI(SceneNode* node) {
  uiNodes_.push_back(node);
}


#endif
