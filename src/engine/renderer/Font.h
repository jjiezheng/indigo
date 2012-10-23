#ifndef FONT_H_
#define FONT_H_

#include <string>
#include <map>

#include "core/Size.h"
#include "maths/Vector2.h"

#include "FontCharacter.h"

class IFntLineParser;

class Font {

public:

  void addCharacter(const FontCharacter& character);

  FontCharacter getCharacter(char character);

  unsigned int texture() const;

  CSize textureSize() const;

  void setTexture(unsigned int textureId);

  void setTextureSize(const CSize& textureSize);

private:

  unsigned int texture_;

  std::map<unsigned int, FontCharacter> characters_;

  CSize textureSize_;

};

inline void Font::setTexture(unsigned int texture) {
  texture_ = texture;
}

inline unsigned int Font::texture() const {
  return texture_;
}

inline CSize Font::textureSize() const {
  return textureSize_;
}

inline void Font::setTextureSize(const CSize& textureSize) {
  textureSize_ = textureSize;
}

#endif