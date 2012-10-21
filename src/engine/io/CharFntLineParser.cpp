#include "CharFntLineParser.h"

#include <sstream>
#include <algorithm>
#include <stdlib.h>

#include "core/String.h"

#include "renderer/FontCharacter.h"
#include "renderer/Font.h"

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
  }

  font->addCharacter(fontCharacter);
} 

CharFntLineParser::~CharFntLineParser() {

}
