#include "Renderer3d.h"

#include "Model.h"
#include "World.h"
#include "Camera.h"
#include "SceneContext.h"

#include "GraphicsInterface.h"

void Renderer3d::render(const Camera& camera, const World& world, const SceneContext& sceneContext) {
//  world.skyBox().render(&camera, sceneContext);
  
  std::vector<Model>::const_iterator it = world.begin();
  for (; it != world.end(); ++it) {
    (*it).render(&camera, sceneContext);
  }
}