#include "Scene.h"

#include "OpenGL.h"

void Scene::init() {
}

void Scene::render() {
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  for (SceneNode* child : children_) {
    child->render(0);
  }
}

void Scene::renderDebug() const {
  
}
