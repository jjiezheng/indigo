#include "TitleScene.h"

#include "TitleSceneUI.h"

TitleScene* TitleScene::scene() {
  TitleScene* scene = new TitleScene();
  scene->init();
  return scene;
}

void TitleScene::init() {
  TitleSceneUI* ui = TitleSceneUI::ui();
  addChild(ui);
}