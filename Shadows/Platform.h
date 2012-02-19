#ifndef CubeFX_Platform_h
#define CubeFX_Platform_h

#include "Standard.h"
#include "Vector2.h"

class Platform {
  
public:
  
  static Platform* platform();
  
public:
  
  virtual void set_screen_size(float width, float height) = 0;
  
  virtual Vector2 screen_size() const = 0;
  
  virtual std::string path_for_file(const std::string& filename) const = 0;
  
  virtual void load_image(const std::string& full_path, INT* width, INT* height, void** data) const = 0;
  
  virtual Vector2 mouse_delta() = 0;
  
  virtual void set_mouse_position(int x, int y) = 0;
  
  virtual Vector2 mouse_position() const = 0;
  
  virtual void set_mouse_state(int buttonId, bool state) = 0;
  
  virtual bool mouse_state(int buttonId) const = 0;
  
  virtual void set_key_state(INT key_code, BOOLEAN state) = 0;
  
  virtual BOOLEAN get_key_state(INT key_code) = 0;

};

#endif
