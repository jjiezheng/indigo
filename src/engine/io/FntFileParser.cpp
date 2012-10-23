#include "FntFileParser.h"

#include <fstream>
#include <stdlib.h>

#include "Path.h"

#include "CharFntLineParser.h"

#include "core/String.h"

#include "renderer/GraphicsInterface.h"

Font FntFileParser::parseFile(const std::string& filePath) {
  std::string fullFilePath = Path::pathForFile(filePath);
  std::ifstream fontStream(fullFilePath.c_str());

  Font font;
  std::string line;
  while (std::getline(fontStream, line)) {
    std::string lineToken = line.substr(0, line.find(" "));
    if (lineToken.compare("char") == 0) {
      std::string lineTokenString = line.substr(line.find(" "), line.length() - line.find(" "));
      CharFntLineParser().parseLine(lineTokenString, &font);
    }

    if (lineToken.compare("page") == 0) {
      std::string lineTokenString = line.substr(line.find(" "), line.length() - line.find(" "));

      std::vector<std::string> lineTokens = String::split(lineTokenString, " ");
      for (std::vector<std::string>::const_iterator i = lineTokens.begin(); i != lineTokens.end(); ++i) {
        if ((*i).compare("") == 0) continue;

        std::vector<std::string> paramTokens = String::split((*i), "=");

        if (paramTokens.front().compare("file") == 0) {
          std::string fileName = String::replace(paramTokens.back(), "\"", "");

          std::string textureFilePath = "fonts/";
          textureFilePath.append(fileName);
          std::string fullTextureFilePath = Path::pathForFile(textureFilePath);

          unsigned int textureId = GraphicsInterface::loadTexture(fullTextureFilePath.c_str());
          font.setTexture(textureId);
        }
      }
    }

    if (lineToken.compare("common") == 0) {
      std::string lineTokenString = line.substr(line.find(" "), line.length() - line.find(" "));

      CSize textureSize;

      std::vector<std::string> lineTokens = String::split(lineTokenString, " ");
      for (std::vector<std::string>::const_iterator i = lineTokens.begin(); i != lineTokens.end(); ++i) {
        if ((*i).compare("") == 0) continue;

        std::vector<std::string> paramTokens = String::split((*i), "=");

        if (paramTokens.front().compare("scaleW") == 0) {
          textureSize.width = atoi(paramTokens.back().c_str());
        }

        if (paramTokens.front().compare("scaleH") == 0) {
          textureSize.height = atoi(paramTokens.back().c_str());
        }
      }

      font.setTextureSize(textureSize);
    }


  }

  return font;
}
