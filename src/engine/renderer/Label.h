#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <vector>

#include "Font.h"

class IEffect;
class Matrix4x4;

class Label {

public:

  Label()
    : labelEffect_(NULL) { };

public:

  static Label* labelWithFont(const std::string& text, const std::string& fontFilePath);

private:

  void init();

private:

  void setText(const std::string& text);

  void generateVertexBuffers();

public:

  void render(const Matrix4x4& projection) const;

private:

  void loadFont(const std::string& fontFilePath);

private:

  IEffect* labelEffect_;

private:

  Font font_;

  std::vector<FontCharacter> characters_;

  std::vector<unsigned int> vertexBuffers_;

};

#endif