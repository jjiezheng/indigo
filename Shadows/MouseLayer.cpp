#include "MouseLayer.h"

#include "Sprite.h"
#include "MacPlatform.h"

#include <iostream>

static const int TAG_MOUSE = 100;

MouseLayer* MouseLayer::mouse() {
  MouseLayer* mouse = new MouseLayer();
  mouse->init();
  return mouse;
}

void MouseLayer::init() {
  Layer2d::init();
  
  scheduleUpdate();
  
  Sprite* mouseSprite = Sprite::sprite("mouse_hand.png");
  addChild(mouseSprite, TAG_MOUSE);
}

void MouseLayer::update(float dt) {
  Vector2 position = MacPlatform::instance()->mouse_position();
  getChildByTag(TAG_MOUSE)->setPosition(position.x, position.y);
}