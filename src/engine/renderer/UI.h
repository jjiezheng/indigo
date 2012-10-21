#ifndef UI_H_
#define UI_H_

#include <vector>

class Label;

class UI {

public:

  void render() const;

public:

  void addLabel(Label* label);

private:

  std::vector<Label*> labels_;

};

inline void UI::addLabel(Label* label) {
  labels_.push_back(label);
}

#endif