#ifndef IFNTLINEPARSER_H_
#define IFNTLINEPARSER_H_

#include <string>

class Font;

class IFntLineParser {

public:

  virtual ~IFntLineParser() { };

public:

  virtual void parseLine(const std::string& line, Font* font) = 0;

};

#endif