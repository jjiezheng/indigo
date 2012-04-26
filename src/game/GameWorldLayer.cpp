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
    light1->translateY(50);
    addChild(light1);
  }

  {    
    DirectionalLight* light1 = DirectionalLight::light(Vector3(1, 1, 1));
    light1->translateZ(50);
    light1->translateY(1);
    light1->setCastsShadows(true);
    addChild(light1);
  }
  
  {  
    Camera* mainCamera = Camera::camera();
    mainCamera->translateZ(35);
    mainCamera->translateY(15);
    mainCamera->rotateX(-60);
    addChild(mainCamera);
  }
  
  {
    Model* book = Model::model("book.blend");
    book->translateZ(30);
    addChild(book);    
  }

  
//  {
//    Model* book = Model::model("book.blend");
//    book->translateZ(30);
//    addChild(book);    
//  }
}

