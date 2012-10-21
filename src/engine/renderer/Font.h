#ifndef FONT_H_
#define FONT_H_

#include <string>
#include <map>

#include "FontCharacter.h"

class IFntLineParser;

class Font {

public:

  void addCharacter(const FontCharacter& character);

  FontCharacter getCharacter(char character);

  void setTexture(unsigned int textureId);

private:

  unsigned int texture_;

  std::map<unsigned int, FontCharacter> characters_;

};

inline void Font::setTexture(unsigned int texture) {
  texture_ = texture;
}

#endif