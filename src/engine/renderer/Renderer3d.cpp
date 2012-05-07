#include "Renderer3d.h"

#include "Model.h"
#include "Shader.h"
#include "World.h"
#include "IViewer.h"
#include "Camera.h"

void Renderer3d::render(const Camera* camera, const World& world, const SceneContext& sceneContext) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glClearColor(backgroundColor_.r, backgroundColor_.g, backgroundColor_.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  world.skyBox().render(camera, sceneContext);
  
  for (Model* node : world) {
    node->render(camera, sceneContext);
  }
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}