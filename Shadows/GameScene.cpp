#include "GameScene.h"

#include "GameSceneView.h"

#include "ModelResource.h"
#include "Model.h"
#include "Box.h"
#include "Light.h"
#include "Camera.h"

static const int TAG_CUBE = 100;

GameScene* GameScene::scene() {
  GameScene* scene = new GameScene();
  scene->init();
  return scene;
}

void GameScene::init() {
  Scene::init();
  
  Camera* defaultCamera = Camera::camera();
  defaultCamera->translateY(2);
  addCamera(defaultCamera);

  Light* light = Light::light(Vector3(1, 1, 1));
  light->setPosition(0, 10, 0);
  addLight(light);

  for (int x = 0; x < 30; x++) {
    for (int z = 0; z < 10; z++) {
      Model* model = Model::model("cube.blend");
      model->translateY(1);
      model->translateZ(8*z);
      model->translateX(8*x);
      addChild(model, TAG_CUBE);
    }
  }
  
  {
    Model* model = Model::model("chun.blend");
    model->translateZ(-10);
    addChild(model, TAG_CUBE);
  }

  
  Model* floor = Model::model("floor.blend");
  addChild(floor);
    
  this->scheduleUpdate();
}

void GameScene::update(float dt) {
//  SceneNode* model = getChildByTag(TAG_CUBE);
//  model->rotateY(1);
}
