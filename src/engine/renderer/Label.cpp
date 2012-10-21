#include "Label.h"

#include "io/FntFileParser.h"

Label* Label::labelWithFont(const std::string& fontFilePath) {
  Label* label = new Label();
  label->loadFont(fontFilePath);
  return label;
}

void Label::loadFont(const std::string& fontFilePath) {
  font_ = FntFileParser::parseFile(fontFilePath);
}

void Label::setText(const std::string& text) {
  characters_.clear();
  for (unsigned int i = 0; i < text.size(); i++) {
    FontCharacter character = font_.getCharacter(text[i]);
    characters_.push_back(character);
  }
}

void Label::render() const {
  for (std::vector<FontCharacter>::const_iterator i = characters_.begin(); i != characters_.end(); ++i) {
    // figure out the uv's probably 1.0f / texturesize
    // forward render them
  }
}
