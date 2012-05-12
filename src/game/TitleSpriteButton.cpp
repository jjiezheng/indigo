#include "TitleSpriteButton.h"

#include "Label.h"
#include "Sprite.h"

#include "MouseClickDispatcher.h"
#include "Vector2.h"

static const int TAG_UP = 100;
static const int TAG_DOWN = 101;

TitleSpriteButton::TitleSpriteButton(Selector* target, SEL_CallFunc handler)
  : target_(target)
  , handler_(handler)
  , isDown_(false) { }

TitleSpriteButton* TitleSpriteButton::button(const char *title, const char *upImage, const char *downImage, Selector* target, SEL_CallFunc handler) {
  TitleSpriteButton* button = new TitleSpriteButton(target, handler);
  button->init(title, upImage, downImage);
  return button;
}

void TitleSpriteButton::init(const char* title, const char* upImage, const char* downImage) {
  Sprite* upSprite = Sprite::sprite(upImage);
  addChild(upSprite, TAG_UP);
  
  Sprite* downSprite = Sprite::sprite(downImage);
  downSprite->setVisible(false);
  addChild(downSprite, TAG_DOWN);

  Label* label = Label::label(title, "copperplate_18.fnt");
  addChild(label);
  
  Rect boundingBox = this->boundingBox();
  Rect labelBoundingBox = label->boundingBox();
  
  float labelX = (boundingBox.width - labelBoundingBox.width) / 2.0f;
  float labelY = (boundingBox.height - labelBoundingBox.height) / 2.0f;
  label->setPosition(labelX, labelY);
  
  MouseClickDispatcher::instance()->addListener(this);
}

void TitleSpriteButton::onMouseDown(int buttonId, const Vector2& location) {
  Rect boundingBox = this->boundingBox();
  if (boundingBox.contains(location)) {
    getChildByTag(TAG_DOWN)->setVisible(true);
    getChildByTag(TAG_UP)->setVisible(false);
    isDown_ = true;
  }
}

void TitleSpriteButton::onMouseUp(int buttonId, const Vector2& location) {
  if (isDown_) {
    getChildByTag(TAG_DOWN)->setVisible(false);
    getChildByTag(TAG_UP)->setVisible(true);  
    if (target_) {
      (target_->*handler_)();
    }
  }
}
