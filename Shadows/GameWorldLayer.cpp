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
    DirectionalLight* light1 = DirectionalLight::light(Vector3(1, 1, 1));
    light1->translateZ(10);
    light1->translateY(1);
    light1->translateX(2);
    light1->rotateY(-5);
    addChild(light1);
  }
  
//  {
//    DirectionalLight* light1 = DirectionalLight::light(Vector3(1, 1, 1));
//    light1->translateZ(50);
//    light1->translateY(1);
//    light1->translateX(-2);
//    light1->rotateY(-5);
//    addChild(light1);
//  }

  
  Camera* mainCamera = Camera::camera();
  mainCamera->translateZ(10);
  addChild(mainCamera);
    

  Model* floor = Model::model("floor.blend");
  floor->translateY(-1);
  addChild(floor);
  
  Model* model = Model::model("cube.blend");
  model->translateZ(-10);
  addChild(model, TAG_CUBE);

}
