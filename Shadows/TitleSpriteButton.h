#ifndef TITLESPRITEBUTTON_H
#define TITLESPRITEBUTTON_H

#include "Button.h"
#include "IMouseClickListener.h"
#include "Selector.h"

class TitleSpriteButton : public Button, public IMouseClickListener {
  
public:
  
  static TitleSpriteButton* button(const char* title, const char* upImage, const char* downImage, Selector* target, SEL_CallFunc handler);
  
private:
  
  void init(const char* title, const char* upImage, const char* downImage);
  
public:
  
  void onMouseDown(int buttonId, const Vector2& location);
  
  void onMouseUp(int buttonId, const Vector2& location);
  
private:
  
  TitleSpriteButton() = default;
  TitleSpriteButton(Selector* target, SEL_CallFunc handler);
  
private:
  
  Selector* target_;
  SEL_CallFunc handler_;
  bool isDown_;
  
};

#endif
