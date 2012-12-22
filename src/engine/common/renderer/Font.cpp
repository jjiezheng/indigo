#include "Font.h"

#include <fstream>

#include "io/Path.h"

void Font::addCharacter(const FontCharacter& character) {
  characters_[character.id] = character;
}

FontCharacter Font::getCharacter(char character) {
  return characters_[character];
}
