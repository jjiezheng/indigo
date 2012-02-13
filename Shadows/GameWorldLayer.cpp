#include "GameWorldLayer.h"

#include "ModelResource.h"
#include "Model.h"
#include "Box.h"
#include "Light.h"
#include "Camera.h"

static const int TAG_CUBE = 100;

GameWorldLayer* GameWorldLayer::layer() {
  GameWorldLayer* layer = new GameWorldLayer();
  layer->init();
  return layer;
}

void GameWorldLayer::init() {
  Camera* defaultCamera = Camera::camera();
  defaultCamera->translateY(2);
  addCamera(defaultCamera);

  {
    Light* light1 = Light::light(Vector3(1, 1, 1));
    light1->setPosition(-50, 10, 0);
    addLight(light1);
  }
  
  {
    Light* light2 = Light::light(Vector3(1, 1, 1));
    light2->setPosition(50, 10, 0);
    addLight(light2);
  }

  
//  for (int x = 0; x < 30; x++) {
//    for (int z = 0; z < 10; z++) {
//      Model* model = Model::model("cube.blend");
//      model->translateY(1);
//      model->translateZ(-(8*z));
//      model->translateX(-(8*x));
//      addChild(model, TAG_CUBE);
//    }
//  }
//  
//  {
//    Model* model = Model::model("chun.blend");
//    model->translateZ(-10);
//    addChild(model, TAG_CUBE);
//  }
  
  
  Model* floor = Model::model("floor.blend");
  addChild(floor);
}