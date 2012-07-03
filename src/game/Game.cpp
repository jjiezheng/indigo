#include "Game.h" 

#include "renderer/Camera.h"
#include "renderer/FogTypes.h"
#include "renderer/WorldLoader.h"

#include "renderer/GraphicsInterface.h"

void Game::init() {
  clock_.init();
  properties_.init();
  
  camera_.translateZ(6.0f);
  
  renderer_.init(GraphicsInterface::screenSize());
  shadowRenderer_.init(GraphicsInterface::screenSize()); 

  camera_.setPerspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);

  WorldLoader loader; 
  loader.loadFromSceneFile("scenes/shadow/shadow.scene", world_, sceneContext_);

  //sceneContext_.setFog(FOG_NONE, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));
}
 
void Game::mainLoop() {
  float dt = clock_.delta_time();
  int fps = clock_.averageFPS();
//  LOG(LOG_CHANNEL_TEMP, "%d", fps);
  camera_.update(dt);
  
  //shadowRenderer_.renderToShadowMap(&light, world_, sceneContext_);
  renderer_.render(&camera_, world_, sceneContext_);
}