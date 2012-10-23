#ifndef UI_H_
#define UI_H_

#include <vector>

#include "core/Size.h"
#include "maths/Matrix4x4.h"

class Label;

class UI {

public:

  void init(const CSize& backBufferSize);

  void render() const;
  
  void update(float dt);

public:

  void addLabel(Label* label);

private:

  std::vector<Label*> labels_;

  Matrix4x4 projection_;

};

inline void UI::addLabel(Label* label) {
  labels_.push_back(label);
}

#endif