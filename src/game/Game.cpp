#include "Game.h" 

#include "core/Standard.h"

#include "renderer/Camera.h"
#include "renderer/FogTypes.h"
#include "renderer/Box.h"
#include "renderer/WorldLoader.h"

#include "renderer/GraphicsInterface.h"

void Game::init() {
  properties_.init();
  
  camera_.translateZ(5.0f);
  camera_.translateY(1.8f);
  
//  shadowRenderer_.init(GraphicsInterface::screenSize()); 
 
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, GraphicsInterface::aspectRatio(), 1.0f, 200.0f);
  camera_.setProjection(projection);

  WorldLoader loader; 
  loader.loadFromSceneFile("scenes/testcars/testcars.scene", world_, sceneContext_);

  sceneContext_.setBackgroundColor(Color3(0.7, 0.5, 0.5));

  //sceneContext_.setFog(FOG_NONE, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));

  //box_.init();
}
 
void Game::mainLoop() {
  Color3 backgroundColor = sceneContext_.backgroundColor();
  GraphicsInterface::clearBuffer(backgroundColor);
  //box_.render();
  float dt = clock_.delta_time();

  camera_.update(dt);
  
  Light light = sceneContext_.lights().front();
  
  //shadowRenderer_.render(&light, world_, sceneContext_);
  renderer_.render(camera_, world_, sceneContext_);

  if (properties_.getProperty(PROPERTY_RENDER_SHADOWMAP)) {
    shadowRenderer_.renderDebug(sceneContext_);
  }
}

void Game::keyUp(char character) {
  properties_.keyUp(character);
}
