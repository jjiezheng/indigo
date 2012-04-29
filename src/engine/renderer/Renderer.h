#ifndef Renderer_H_
#define Renderer_H_

#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

#include <vector>

class SceneNode;
class Light;
class DirectionalLight;
class PointLight;
class Model;
class Shader;
class Camera;
class ShadowMap;
class Mesh;
class Box;

class Renderer {
  
public:
  
  static Renderer* renderer();
  
private:
  
  Renderer();

public:
  
  void init();
  
  void render(Camera* camera, SceneNode* sceneNode);
  
private:
  
  void renderScene(Shader* shader);
  
  void renderUI();
  void render3d(Camera* camera);
  void renderShadowMap();
  void renderDebug();
  
public:
  
  void queuePointLight(PointLight* light);
  
  void queueDirectionalLight(DirectionalLight* light);
  
  void queueShadowLight(Light* light);
  
  void queueLight(Light* light);
  
  void queueModel(Model* model);
  
  void queueCamera(Camera* camera);
  
  void queueUI(SceneNode* node);
  
  void queueDebug(SceneNode* node);
  
  void queueMesh(Mesh* node);
  
private:
  
  std::vector<Camera*> cameras_;
  std::vector<Mesh*> meshes_;

  std::vector<DirectionalLight*> directionalLights_;
  std::vector<PointLight*> pointLights_;
  std::vector<Light*> shadowLights_;
  std::vector<Light*> lights_;
  
  std::vector<SceneNode*> uiNodes_;

  std::vector<SceneNode*> debugNodes_;
  
private:

  ShadowMap* shadowMap_;
  
};

inline
void Renderer::queueMesh(Mesh* node) {
  meshes_.push_back(node);
}

inline
void Renderer::queueCamera(Camera* camera) {
  cameras_.push_back(camera);
}

inline
void Renderer::queueDirectionalLight(DirectionalLight* light) {
  directionalLights_.push_back(light);
}

inline
void Renderer::queuePointLight(PointLight* light) {
  pointLights_.push_back(light);
}

inline
void Renderer::queueShadowLight(Light* light) {
  shadowLights_.push_back(light);
}

inline
void Renderer::queueLight(Light* light) {
  lights_.push_back(light);
}

inline
void Renderer::queueUI(SceneNode* node) {
  uiNodes_.push_back(node);
}


inline
void Renderer::queueDebug(SceneNode* node) {
  debugNodes_.push_back(node);
}

#endif
