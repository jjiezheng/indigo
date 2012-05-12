#include "Renderer3d.h"

#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "SceneContext.h"

void Renderer3d::render(const Camera& camera, const World& world, const SceneContext& sceneContext) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  Color3 backgroundColor = sceneContext.backgroundColor();
  glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, 1.0f);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  world.skyBox().render(&camera, sceneContext);
  
  std::vector<Model>::const_iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it).render(&camera, sceneContext);
  }
  
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
}