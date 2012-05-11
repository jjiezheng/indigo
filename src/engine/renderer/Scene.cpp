#include "Scene.h"

#include "OpenGL.h"

void Scene::init() {
}

void Scene::render() {
  glClearColor(1, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    (*it)->render(0);
  }
}

void Scene::renderDebug() const {
  
}
