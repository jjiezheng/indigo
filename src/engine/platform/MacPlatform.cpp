#include "MacPlatform.h"

#include "windows.h"

#include <GL/glfw.h>
#include <IL/ilu.h>

#include <iostream>
#include "core/String.h"

static MacPlatform* platform_ = 0;

MacPlatform* MacPlatform::instance() {
  if (!platform_) {
    platform_ = new MacPlatform(); 
  }
  return platform_;
}

MacPlatform::MacPlatform() {
  //  FreeImage_Initialise();
  ilInit();

  for (int i = 0; i < KEY_STATE_COUNT; i++) {
    key_states_[i] = false;
  }
}

std::string MacPlatform::path_for_file(const std::string& filename) const {
  char szFileName[MAX_PATH];
  HINSTANCE hInstance = GetModuleHandle(NULL);
  GetModuleFileName(hInstance, szFileName, MAX_PATH);
  String exePath = String(szFileName).pathComponent();
  String assetsPath = exePath.addPathComponent("assets");
  String fullPath = assetsPath.addPathComponent(filename);
  return fullPath.str();
}

void MacPlatform::load_image(const std::string& full_path, int* width, int* height, void* data) const {
  if (!ilLoadImage(full_path.c_str())) {
    LOG(LOG_CHANNEL_IMAGELOAD, "failed to load image", full_path.c_str());
  }
  *width = ilGetInteger(IL_IMAGE_WIDTH); 
  *height = ilGetInteger(IL_IMAGE_HEIGHT); 
  data = ilGetData();
}

void MacPlatform::set_key_state(int key_code, bool state) {
  key_states_[key_code] = state;
}

bool MacPlatform::get_key_state(int key_code) {
  return key_states_[key_code];
}

void MacPlatform::set_mouse_position(int x, int y) {
  last_mouse_position_ = mouse_position_;
  mouse_position_.x = x;
  mouse_position_.y = y;
  if (!mouse_input_ready_) {
    mouse_input_ready_ = true;
  } else {
    mouse_position_changed_ = true;
  }
}

Vector2 MacPlatform::mouse_delta() { 
  if (mouse_position_changed_ && mouse_input_ready_) {
    mouse_position_changed_ = false;
    Vector2 delta = mouse_position_ - last_mouse_position_;
    return delta;
  }
  return Vector2::IDENTITY;
}
