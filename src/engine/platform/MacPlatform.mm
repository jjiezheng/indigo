#include "MacPlatform.h"

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

void MacPlatform::load_image(const std::string& full_path, int* width, int* height, void** data, int* format) const {
  NSString* path = [NSString stringWithUTF8String:full_path.c_str()];  
  NSData *texData = [[[NSData alloc] initWithContentsOfFile:path] autorelease];
  
  NSBitmapImageRep* image = [[[NSBitmapImageRep alloc] initWithData:texData] autorelease];
  
  if (image == nil) {
    NSLog(@"Failed to load image %s", full_path.c_str());
  }
  
  *width = (int)CGImageGetWidth(image.CGImage);
  *height = (int)CGImageGetHeight(image.CGImage);
  CGColorSpaceRef colorSpace = CGColorSpaceCreateDeviceRGB();
  *data = malloc(*height * *width * 4);
  CGContextRef context = CGBitmapContextCreate(*data, *width, *height, 8, 4 * *width, colorSpace, kCGImageAlphaPremultipliedLast | kCGBitmapByteOrder32Big );
  CGColorSpaceRelease(colorSpace);
  
  CGRect bounds = CGRectMake(0, 0, *width, *height) ;
  CGContextClearRect(context, bounds);
  //  CGContextTranslateCTM(context, 0, *height);
  //  CGContextScaleCTM(context, 1.0, -1.0);
  CGContextDrawImage(context, bounds, image.CGImage);
  CGContextRelease(context);
  
  *format = GL_RGBA;
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
