#include "Path.h"

#include <Foundation/Foundation.h>
#include <ApplicationServices/ApplicationServices.h>

std::string Path::pathForFile(const std::string &filename) {
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  NSString* objc_filename = [NSString stringWithUTF8String:filename.c_str()];
  
  NSString* basename = [[objc_filename lastPathComponent] stringByDeletingPathExtension];
  NSString* extension = [objc_filename pathExtension];
  NSString* path = [[NSBundle mainBundle] pathForResource:basename ofType:extension];
  
  std::string final_path = !path ? filename : [path cStringUsingEncoding:NSUTF8StringEncoding];
  
  [pool release];
  return final_path;
}
