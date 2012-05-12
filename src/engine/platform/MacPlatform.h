#ifndef Shadows_MacPlatform_h
#define Shadows_MacPlatform_h

#include "maths/Vector2.h"

#define KEY_STATE_COUNT 256

enum MouseButtons {
  MOUSE_1,
  MOUSE_2,
  MAX_MOUSE_BUTTONS
};

class MacPlatform {
  
public:
  
  static MacPlatform* instance();
  
public:
  
  MacPlatform();
  
public:
  
  void set_screen_size(int width, int height);
  
  Vector2 screen_size() const;
  
  float aspect_ratio() const;
  
  std::string path_for_file(const std::string& filename) const;
  
  void load_image(const std::string& full_path, int* width, int* height, void** data) const;
  
  void set_mouse_position(int x, int y);
  
  Vector2 mouse_position() const;
  
  Vector2 mouse_delta();
  
  void set_mouse_delta(int x, int y);
  
  void set_mouse_state(int buttonId, bool state);
  
  bool mouse_state(int buttonId) const;
  
  void set_key_state(int key_code, bool state);
  
  bool get_key_state(int key_code);
  
private:
  
  bool mouse_input_ready_;
  
  bool mouse_position_changed_;
  
  Vector2 last_mouse_position_;
  
  Vector2 mouse_position_;
  
  Vector2 screen_size_;
  
  float aspect_ratio_;
  
  bool key_states_[KEY_STATE_COUNT];
  
  bool mouseState[10];
  
};

inline
void MacPlatform::set_mouse_state(int buttonId, bool state) {
  if (buttonId >= MAX_MOUSE_BUTTONS) return;
  mouseState[buttonId] = state;
}

inline
bool MacPlatform::mouse_state(int buttonId) const {
  if (buttonId >= MAX_MOUSE_BUTTONS) return false;
  return mouseState[buttonId];
}

inline
Vector2 MacPlatform::mouse_position() const {
  return mouse_position_;
}

inline
void MacPlatform::set_screen_size(int width, int height) {
  screen_size_.x = (float)width;
  screen_size_.y = (float)height;
  aspect_ratio_ = (float)width/(float)height;
}

inline
Vector2 MacPlatform::screen_size() const {
  return screen_size_;
}

inline 
float MacPlatform::aspect_ratio() const {
  return aspect_ratio_;
}


#endif
