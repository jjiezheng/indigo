#include "MouseLayer.h"

#include <iostream>

#include "platform/MacPlatform.h"

#include "Sprite.h"

static const int TAG_MOUSE = 100;

MouseLayer* MouseLayer::mouse() {
  MouseLayer* mouse = new MouseLayer();
  mouse->init();
  return mouse;
}

void MouseLayer::init() {
  scheduleUpdate();
  
  Sprite* mouseSprite = Sprite::sprite("mouse_hand.png");
  addChild(mouseSprite, TAG_MOUSE);
}

void MouseLayer::update(float dt) {
  Vector2 position = MacPlatform::instance()->mouse_position();
  SceneNode* mouseNode = getChildByTag(TAG_MOUSE);
  mouseNode->setPosition(position.x, position.y - mouseNode->boundingBox().height);
}
