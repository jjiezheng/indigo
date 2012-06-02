#include "Game.h" 

#include "renderer/Camera.h"
#include "renderer/FogTypes.h"
#include "renderer/WorldLoader.h"

#include "renderer/GraphicsInterface.h"

void Game::init() {
  properties_.init();
  
  camera_.translateZ(5.0f);
  camera_.translateY(1.8f);
  
  shadowRenderer_.init(GraphicsInterface::screenSize()); 
 
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
  camera_.setProjection(projection);

  WorldLoader loader; 
  loader.loadFromSceneFile("scenes/testcars/testcars.scene", world_, sceneContext_);

  sceneContext_.setBackgroundColor(Color3(0, 0, 0));

  //sceneContext_.setFog(FOG_NONE, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  camera_.update(dt);
  
  Light light = sceneContext_.lights().front();
  shadowRenderer_.renderToShadowMap(&light, world_, sceneContext_);
  renderer_.render(&camera_, world_, sceneContext_);
}