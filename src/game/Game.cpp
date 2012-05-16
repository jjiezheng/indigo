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
  
  //shadowRenderer_.init(Window::screenSize());
 
  Matrix4x4 projection = Matrix4x4::perspective(45.0f, Window::aspectRatio(), 1.0f, 200.0f);
  camera_.setProjection(projection);
  
  WorldLoader loader; 
  loader.loadFromSceneFile("scenes/testcars/testcars.scene", world_, sceneContext_);

  sceneContext_.setFog(FOG_NONE, 0.66f, -10, -100, Color4(0.6f, 0.6f, 0.6f));
  sceneContext_.setBackgroundColor(Color3( 0.4f, 0.6f, 0.93f));
  
//  box_.init();
}
 
void Game::mainLoop() { 
//  glClearColor(0.0, 1.0, 0.0, 1.0);
//  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  box_.render();
  float dt = clock_.delta_time(); 

  camera_.update(dt);
  
  //shadowRenderer_.render(world_, sceneContext_);
  renderer_.render(camera_, world_, sceneContext_);

  if (properties_.getProperty(PROPERTY_RENDER_SHADOWMAP)) {
    shadowRenderer_.renderDebug(sceneContext_);
  }
}

void Game::keyUp(char character) {
  properties_.keyUp(character);
}
