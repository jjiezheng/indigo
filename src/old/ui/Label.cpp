#include "Label.h"

#include <iostream>

#include "core/Standard.h"
#include "renderer/TextureCache.h"
#include "renderer/Texture.h"
#include "renderer/Shader.h"

#include "FontDescriptor.h"
#include "FontCharacter.h"

Label* Label::label(const char* text, const char* fontFile) {
  Label* label = new Label();
  label->init(fontFile);
  label->setText(text);
  return label;
}

void Label::setText(const String& text) {
  removeAllChildrenAndCleanup();
  text_ = text;
  float offset = 0;
  String::ConstIterator it = text.begin();
  for (; it != text.end(); ++it) {
    FontCharacterInfo character_info = font_->charInfo((*it));
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
  
  glBindTexture(GL_TEXTURE_2D, texture_->textureId());
  shader->set_uniform(0, "colorMap");

  std::vector<SceneNode*>::const_iterator it = children_.begin();
  for (; it != children_.end(); ++it) {
    (*it)->render(shader);
  }
  glDisable(GL_BLEND);
}

void Label::queueRender(Renderer* renderer) {
}

void Label::renderDebug() const {
  
}
