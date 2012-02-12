#ifndef Shadows_MacPlatform_h
#define Shadows_MacPlatform_h

#include "Platform.h"

#define KEY_STATE_COUNT 256

class MacPlatform : public Platform {
  
public:
  
  static MacPlatform* instance();
  
public:
  
  MacPlatform();
  
public:
  
  void set_screen_size(float width, float height);
  
  VEC2 screen_size() const;
  
  float aspect_ratio() const;
  
  std::string path_for_file(const std::string& filename) const;
  
  void load_image(const std::string& full_path, INT* width, INT* height, void** data) const;
  
  void set_mouse_position(int x, int y);
  
  Vector2 mouse_position() const;
  
  VEC2 mouse_delta();
  
  void set_mouse_delta(INT x, INT y);
  
  void set_key_state(INT key_code, BOOLEAN state);
  
  BOOLEAN get_key_state(INT key_code);
  
private:
  
  VEC2 mouse_delta_;
  
  Vector2 mouse_position_;
  
  VEC2 screen_size_;
  
  float aspect_ratio_;
  
  BOOLEAN key_states_[KEY_STATE_COUNT];
  
};

inline
void MacPlatform::set_mouse_position(int x, int y) {
  mouse_position_.x = x;
  mouse_position_.y = y;
}

inline
Vector2 MacPlatform::mouse_position() const {
  return mouse_position_;
}

inline
void MacPlatform::set_screen_size(float width, float height) {
  screen_size_.x = width;
  screen_size_.y = height;
  aspect_ratio_ = width/height;
}

inline
VEC2 MacPlatform::screen_size() const {
  return screen_size_;
}

inline 
float MacPlatform::aspect_ratio() const {
  return aspect_ratio_;
}
#endif
