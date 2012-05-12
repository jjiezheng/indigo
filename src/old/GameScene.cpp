#include "GameScene.h"

#include "GameWorldLayer.h"
#include "GameUILayer.h"

GameScene* GameScene::scene() {
  GameScene* scene = new GameScene();
  scene->init();
  return scene;
}

void GameScene::init() {
  GameWorldLayer* worldLayer = GameWorldLayer::layer();
  addChild(worldLayer);
  
  GameUILayer* uiLayer = GameUILayer::layer();
  addChild(uiLayer);
}
