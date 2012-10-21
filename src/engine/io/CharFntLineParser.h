#ifndef CHARFNTLINEPARSER_H_
#define CHARFNTLINEPARSER_H_

#include <vector>

#include "IFntLineParser.h"

#include "ICharFntTokenParser.h"

class CharFntLineParser : public IFntLineParser {

public:

  ~CharFntLineParser();

public:

  void parseLine(const std::string& line, Font* font);

private:

  std::vector<ICharFntTokenParser*> tokenParser_;

};

#endif