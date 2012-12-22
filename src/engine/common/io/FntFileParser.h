#ifndef FNTFILEPARSER_H_
#define FNTFILEPARSER_H_

#include "renderer/Font.h"

class FntFileParser {

public:

  static Font parseFile(const std::string& filePath);

};

#endif