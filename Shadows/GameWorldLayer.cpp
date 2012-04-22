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
    mainCamera->translateZ(50);
    mainCamera->translateY(1);
    addChild(mainCamera);
  }
  
  {
    Model* ball = Model::model("ball.blend");
    ball->translateZ(30);
    addChild(ball);
    
    Model* smallPlane = Model::model("small_plane.blend");
    smallPlane->rotateX(90);
    smallPlane->translateZ(20);
    addChild(smallPlane);
      
    Model* largePlane = Model::model("large_plane.blend");
    largePlane->rotateX(90);
    addChild(largePlane);

    
    Model* floor = Model::model("floor.blend");
    addChild(floor);
    
    for (int x = 0; x < 10; x++) {
      for (int z = 0; z < 10; z++) {
        Model* model = Model::model("cube.blend");
        model->translateZ(-z*5);
        model->translateX(-x*5);
        addChild(model, TAG_CUBE);
      }
    }
    
    Model* wall = Model::model("wall.blend");
    wall->translateZ(-20);
    wall->translateY(-5);
    addChild(wall, TAG_CUBE);
    
    Model* monkey = Model::model("monkey.blend");
    monkey->translateZ(20);
    addChild(monkey);
  }
}

