#include "TitleSceneUI.h"

#include "TitleSpriteButton.h"
#include "MacPlatform.h"

#include <iostream>

TitleSceneUI* TitleSceneUI::ui() {
  TitleSceneUI* ui = new TitleSceneUI();
  ui->init();
  return ui;
}

void TitleSceneUI::init() {
  Layer2d::init();
  
  Button* button = TitleSpriteButton::button("Play!", "button_up.png", "button_down.png");
  Vector2 screenSize = MacPlatform::instance()->screen_size();
  Rectangle buttonSize = button->boundingBox();
  addChild(button);
  button->setPosition((screenSize.x - buttonSize.width)/2.0f, 
                      (screenSize.y - buttonSize.height)/2.0f);
}