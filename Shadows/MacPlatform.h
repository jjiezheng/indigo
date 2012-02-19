#ifndef Shadows_MacPlatform_h
#define Shadows_MacPlatform_h

#include "Platform.h"
#include "Vector2.h"

#define KEY_STATE_COUNT 256

enum MouseButtons {
  MOUSE_1,
  MOUSE_2,
  MAX_MOUSE_BUTTONS
};

class MacPlatform : public Platform {
  
public:
  
  static MacPlatform* instance();
  
public:
  
  MacPlatform();
  
public:
  
  void set_screen_size(float width, float height);
  
  Vector2 screen_size() const;
  
  float aspect_ratio() const;
  
  std::string path_for_file(const std::string& filename) const;
  
  void load_image(const std::string& full_path, INT* width, INT* height, void** data) const;
  
  void set_mouse_position(int x, int y);
  
  Vector2 mouse_position() const;
  
  Vector2 mouse_delta();
  
  void set_mouse_delta(INT x, INT y);
  
  void set_mouse_state(int buttonId, bool state);
  
  bool mouse_state(int buttonId) const;
  
  void set_key_state(INT key_code, BOOLEAN state);
  
  BOOLEAN get_key_state(INT key_code);
  
private:
  
  bool mouse_input_ready_;
  
  bool mouse_position_changed_;
  
  Vector2 last_mouse_position_;
  
  Vector2 mouse_position_;
  
  Vector2 screen_size_;
  
  float aspect_ratio_;
  
  BOOLEAN key_states_[KEY_STATE_COUNT];
  
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
void MacPlatform::set_screen_size(float width, float height) {
  screen_size_.x = width;
  screen_size_.y = height;
  aspect_ratio_ = width/height;
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
