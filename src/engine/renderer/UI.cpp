#include "UI.h"

#include "Label.h"

void UI::render() const {
  for (std::vector<Label*>::const_iterator i = labels_.begin(); i != labels_.end(); ++i) {
    (*i)->render();
  }
}
