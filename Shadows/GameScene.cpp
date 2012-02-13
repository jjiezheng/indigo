#include "GameScene.h"

#include "GameWorldLayer.h"

GameScene* GameScene::scene() {
  GameScene* scene = new GameScene();
  scene->init();
  return scene;
}

void GameScene::init() {
  GameWorldLayer* worldLayer = GameWorldLayer::layer();
  addChild(worldLayer);      
}
