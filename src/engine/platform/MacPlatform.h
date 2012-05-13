#ifndef MACPLATFORM_H
#define MACPLATFORM_H

#include <string>
#include "maths/Vector2.h"

class MacPlatform {
  
public:
  
  static float aspectRatio();
  
  static int screenWidth();
  
  static int screenHeight();
  
  static Vector2 screenSize();
  
public:
  
  static std::string path_for_file(const std::string& filename);
  
  static void load_image(const std::string& full_path, int* width, int* height, void** data, int* format);
    
};

#endif
