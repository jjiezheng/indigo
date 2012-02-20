#include "GameUILayer.h"

#include "FPSLabel.h"

GameUILayer* GameUILayer::layer() {
  GameUILayer* layer = new GameUILayer();
  layer->init();
  return layer;
}

void GameUILayer::init() {  
//  FPSLabel* fps = FPSLabel::label();
//  addChild(fps);
}

