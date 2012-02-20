#include "GameWorldLayer.h"

#include "ModelResource.h"
#include "Model.h"
#include "Box.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "Camera.h"

static const int TAG_CUBE = 100;

GameWorldLayer* GameWorldLayer::layer() {
  GameWorldLayer* layer = new GameWorldLayer();
  layer->init();
  return layer;
}

void GameWorldLayer::init() {
  {
    PointLight* light1 = PointLight::light(Vector3(1, 1, 1));
    light1->setCastsShadows(true);
    light1->translateY(5);
    light1->translateZ(10);
    addChild(light1);
  }
  
  Camera* mainCamera = Camera::camera();
  mainCamera->translateZ(10);
  addChild(mainCamera);
    
  Model* floor = Model::model("floor.blend");
  floor->translateY(-1);
  addChild(floor);
  
  Model* wall = Model::model("wall.blend");
  wall->translateZ(-20);
  addChild(wall);
  
  for (int x = 0; x < 10; x++) {
    Model* model = Model::model("cube.blend");
    model->translateZ(-10);
    model->translateX(-x*5);
    addChild(model, TAG_CUBE);
  }
  
//  Model* monkey = Model::model("monkey.blend");
//  addChild(monkey);
}
