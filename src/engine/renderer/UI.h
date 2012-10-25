#ifndef UI_H_
#define UI_H_

#include <vector>

#include "core/Size.h"
#include "maths/Matrix4x4.h"

class Label;
class Control;

class UI {

public:

  void init(const CSize& backBufferSize);

  void render() const;
  
  void update(float dt);

public:

	void addControl(Control* control);

private:

	std::vector<Control*> controls_;

  Matrix4x4 projection_;

};

inline void UI::addControl(Control* control) {
  controls_.push_back(control);
}

#endif