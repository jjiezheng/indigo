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
    : labelEffect_(NULL)
    , lastDeltaTime_(1.0f/60.0f) { };

public:

  static Label* labelWithFont(const std::string& text, const std::string& fontFilePath);

private:

  void init();

private:

  void setText(const std::string& text);

public:

  void setPosition(int x, int y);

public:

  void render(const Matrix4x4& projection) const;

  void update(float dt);

private:

  void loadFont(const std::string& fontFilePath);

private:

  IEffect* labelEffect_;

private:

  Font font_;

  std::vector<FontCharacter> characters_;
  std::vector<unsigned int> vertexBuffers_;

  float lastDeltaTime_;

  int x_;
  int y_;

};

inline void Label::setPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

#endif