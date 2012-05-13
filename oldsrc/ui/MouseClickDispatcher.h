#ifndef MouseClickDispatcher_H_
#define MouseClickDispatcher_H_

#include <vector>

class Vector2;
class IMouseClickListener;

class MouseClickDispatcher {
  
public:
  
  static MouseClickDispatcher* instance();
  
public:
  
  void mouseDown(int buttonId, const Vector2& location);
  
  void mouseUp(int buttonId, const Vector2& location);
  
public:
  
  void addListener(IMouseClickListener* listener);
  
private:
  
  MouseClickDispatcher() { };
  
private:
  
  std::vector<IMouseClickListener*> listeners_;
  
};

#endif
