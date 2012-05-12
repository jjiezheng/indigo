#include "MacPlatform.h"

//extern "C" {
//  #include <FreeImage.h>
//}

#include <IL/ilu.h>

#include <sys/sysctl.h>
#include <sys/time.h>
#include <iostream>

#include <Foundation/Foundation.h>
#include <ApplicationServices/ApplicationServices.h>

static MacPlatform* platform_ = 0;

MacPlatform* MacPlatform::instance() {
  if (!platform_) {
    platform_ = new MacPlatform(); 
  }
  return platform_;
}

MacPlatform::MacPlatform() {
  ilInit();
  
  for (int i = 0; i < KEY_STATE_COUNT; i++) {
    key_states_[i] = false;
  }
}

std::string MacPlatform::path_for_file(const std::string& filename) const {
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  NSString* objc_filename = [NSString stringWithUTF8String:filename.c_str()];
  
  NSString* basename = [[objc_filename lastPathComponent] stringByDeletingPathExtension];
  NSString* extension = [objc_filename pathExtension];
  NSString* path = [[NSBundle mainBundle] pathForResource:basename ofType:extension];
  
  
  
  std::string final_path = !path ? filename : [path cStringUsingEncoding:NSUTF8StringEncoding];
    
  [pool release];
  return final_path;
}

void MacPlatform::load_image(const std::string& full_path, int* width, int* height, void** data) const {
  ilLoadImage(full_path.c_str());
  
  *width =  ilGetInteger(IL_IMAGE_WIDTH);
  *height = ilGetInteger(IL_IMAGE_HEIGHT);
  *data = ilGetData();  
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
