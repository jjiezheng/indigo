#ifndef PLATFORM_H
#define PLATFORM_H

#include <string>
#include "core/Size.h"

class Platform {
  
public:
  
  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static CSize screenSize();
  
public:
  
  static std::string path_for_file(const std::string& filename);
  
  static void load_image(const std::string& full_path, int* width, int* height, void** data, int* format);
    
};

#endif
