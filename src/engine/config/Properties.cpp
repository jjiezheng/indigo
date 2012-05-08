#include "properties.h"

#include <iostream>

void Properties::init() {
  properties_.insert(std::make_pair(PROPERTY_RENDER_SHADOWMAP, false));
}

bool Properties::getProperty(char character) {
  if (properties_.find(character) != properties_.end()) {
    return properties_[character];
  }
  return false;
}

void Properties::keyUp(char character) {
  if (properties_.find(character) != properties_.end()) {
    std::clog << character << std::endl;
    properties_[character] = !properties_[character];
  }
}
