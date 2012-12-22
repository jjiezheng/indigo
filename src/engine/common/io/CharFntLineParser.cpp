#include "CharFntLineParser.h"

#include <sstream>
#include <algorithm>
#include <stdlib.h>

#include "core/String.h"

#include "renderer/FontCharacter.h"
#include "renderer/Font.h"
#include "renderer/Geometry.h"

void CharFntLineParser::parseLine(const std::string& line, Font* font) {
  FontCharacter fontCharacter;

  std::vector<std::string> lineTokens = String::split(line, " ");
  for (std::vector<std::string>::const_iterator i = lineTokens.begin(); i != lineTokens.end(); ++i) {
    if ((*i).compare("") == 0) continue;

    std::vector<std::string> paramTokens = String::split((*i), "=");
    
    if (paramTokens.front().compare("id") == 0) {
      fontCharacter.id = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("x") == 0) {
      fontCharacter.x = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("y") == 0) {
      fontCharacter.y = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("width") == 0) {
      fontCharacter.width = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("height") == 0) {
      fontCharacter.height = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("xoffset") == 0) {
      fontCharacter.xoffset = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("yoffset") == 0) {
      fontCharacter.yoffset = atoi(paramTokens.back().c_str());
    }

    if (paramTokens.front().compare("xadvance") == 0) {
      fontCharacter.xadvance = atoi(paramTokens.back().c_str());
    }
  }

  CSize characterSize(fontCharacter.width, fontCharacter.height);
  CSize characterOffset(fontCharacter.x, fontCharacter.y);
  unsigned int vertexBuffer = Geometry::fontCharacter(characterSize, characterOffset, font->textureSize());

  fontCharacter.vertexBuffer = vertexBuffer;

  font->addCharacter(fontCharacter);
} 

CharFntLineParser::~CharFntLineParser() {

}
