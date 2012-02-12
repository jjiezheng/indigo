#ifndef TITLESPRITEBUTTON_H
#define TITLESPRITEBUTTON_H

#include "Button.h"

class TitleSpriteButton : public Button {
  
public:
  
  static TitleSpriteButton* button(const char* title, const char* upImage, const char* downImage);
  
private:
  
  void init(const char* title, const char* upImage, const char* downImage);
  
private:
  
  TitleSpriteButton() = default;
  
};

#endif
