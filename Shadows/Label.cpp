#include "Label.h"

#include "FontDescriptor.h"
#include "FontCharacter.h"

#include "TextureCache.h"
#include "Texture.h"

#include "Standard.h"
#include "Renderer.h"

Label* Label::label(const char* text, const char* fontFile) {
  Label* label = new Label();
  label->init(fontFile);
  label->setText(text);
  return label;
}

void Label::setText(const char *text) {
  removeAllChildrenAndCleanup();
  text_ = text;
  float offset = 0;
  for (char chr : text_) {
    FontCharacterInfo character_info = font_->charInfo(chr);
    FontCharacter* character = FontCharacter::character(&character_info);
    character->setPosition(offset, 0);
    addChild(character);
    offset += character_info.width;
  }
}

void Label::init(const char *fontFile) {
  font_ = FontDescriptor::descriptor(fontFile);
  texture_ = TextureCache::instance()->addTexture(font_->asset().c_str());
}

void Label::render(Shader *shader) const {
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  texture_->render(shader);
  
  for (SceneNode* child : children_) {
    child->render(shader);
  }
  glDisable(GL_BLEND);
}

void Label::render(Renderer* renderer) {
  renderer->queueUI(this);
}
