#include "TitleSpriteButton.h"

#include "Label.h"
#include "Sprite.h"

TitleSpriteButton* TitleSpriteButton::button(const char* title, const char* upImage, const char* downImage) {
  TitleSpriteButton* button = new TitleSpriteButton();
  button->init(title, upImage, downImage);
  return button;
}

void TitleSpriteButton::init(const char* title, const char* upImage, const char* downImage) {
  Sprite* upSprite = Sprite::sprite(upImage);
  addChild(upSprite);
  
  Sprite* downSprite = Sprite::sprite(downImage);
  downSprite->setVisible(false);
  addChild(downSprite);

  Label* label = Label::label(title, "copperplate_18.fnt");
  addChild(label);
  
  Rectangle boundingBox = this->boundingBox();
  Rectangle labelBoundingBox = label->boundingBox();
  
  float labelX = (boundingBox.width - labelBoundingBox.width) / 2.0f;
  float labelY = (boundingBox.height - labelBoundingBox.height) / 2.0f;
  label->setPosition(labelX, labelY);
}