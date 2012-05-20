#include "Game.h" 

#include "core/Standard.h"

#include "renderer/Camera.h"
#include "renderer/FogTypes.h"
#include "renderer/Box.h"
#include "renderer/WorldLoader.h"

#include "app/Window.h"

void Game::init() { 
  properties_.init();
  
  camera_.translateZ(10.0f);
  camera_.translateY(1.8f);
  
  shadowRenderer_.init(Window::screenSize()); 
 
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, Window::aspectRatio(), 1.0f, 200.0f);
  camera_.setProjection(projection);
  
  WorldLoader loader; 
  loader.loadFromSceneFile("scenes/testcars/testcars.scene", world_, sceneContext_); 

  sceneContext_.setFog(FOG_NONE, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));
}
 
void Game::mainLoop() { 
  float dt = clock_.delta_time();

  camera_.update(dt);
  
  Light light = sceneContext_.lights().front();
  
  shadowRenderer_.render(&light, world_, sceneContext_);
  renderer_.render(camera_, world_, sceneContext_);

  if (properties_.getProperty(PROPERTY_RENDER_SHADOWMAP)) {
    shadowRenderer_.renderDebug(sceneContext_);
  }
}

void Game::keyUp(char character) {
  properties_.keyUp(character);
}
