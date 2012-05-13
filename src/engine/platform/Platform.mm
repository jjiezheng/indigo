#include "Platform.h"

#include <Foundation/Foundation.h>
#include <ApplicationServices/ApplicationServices.h>
#include <GL/glfw.h>

float Platform::aspectRatio() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return (float)width/(float)height;
}

int Platform::screenWidth() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return width;
}

int Platform::screenHeight() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return height;  
}

CSize Platform::screenSize() {
  int width, height = 0;
  glfwGetWindowSize(&width, &height);
  return CSize(width, height);
}

std::string Platform::path_for_file(const std::string& filename) {
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  NSString* objc_filename = [NSString stringWithUTF8String:filename.c_str()];
  
  NSString* basename = [[objc_filename lastPathComponent] stringByDeletingPathExtension];
  NSString* extension = [objc_filename pathExtension];
  NSString* path = [[NSBundle mainBundle] pathForResource:basename ofType:extension];
  
  std::string final_path = !path ? filename : [path cStringUsingEncoding:NSUTF8StringEncoding];
    
  [pool release];
  return final_path;
}

void Platform::load_image(const std::string& full_path, int* width, int* height, void** data, int* format) {
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
  CGContextDrawImage(context, bounds, image.CGImage);
  CGContextRelease(context);
  
  *format = GL_RGBA;
}

