#ifndef PROPERTIES_H
#define PROPERTIES_H

#include <map>
#include "HashedString.h"

enum PropertyType {
  PROPERTY_RENDER_SHADOWMAP = 'g'
};

class Properties {
  
public:
  
  void init();
  
  bool getProperty(char character);
  
  void keyUp(char character);
  
private:
  
  std::map<char, bool> properties_;
  
};

#endif
