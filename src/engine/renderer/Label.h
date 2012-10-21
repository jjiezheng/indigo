#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <vector>

#include "Font.h"

class Label {

public:

  static Label* labelWithFont(const std::string& fontFilePath);

public:

  void setText(const std::string& text);

public:

  void render() const;

private:

  void loadFont(const std::string& fontFilePath);

private:

  Font font_;

  std::vector<FontCharacter> characters_;

};

#endif