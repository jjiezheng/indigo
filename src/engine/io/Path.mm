#include "Path.h"

#include <Foundation/Foundation.h>
#include <ApplicationServices/ApplicationServices.h>

std::string Path::pathForFile(const std::string &filename) {
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
  
  NSString* objcFilename = [NSString stringWithCString:filename.c_str() encoding:NSUTF8StringEncoding];
  NSString* path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:objcFilename];
  
  std::string finalPath = [path cStringUsingEncoding:NSUTF8StringEncoding];
  
  [pool release];
  return finalPath;
}
