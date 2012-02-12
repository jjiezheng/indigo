#ifndef CubeFX_IOSPlatform_h
#define CubeFX_IOSPlatform_h

#include "Platform.h"

class IOSPlatform : public Platform {
  
public:
  
  FLOAT screen_width() const;
  
  FLOAT screen_height() const;
  
  FLOAT screen_orientation() const;
  
  INT thread_count() const;
  
  std::string path_for_file(const std::string& filename) const;
  
  float delta_time() const;
  
  void load_image(const std::string& full_path, INT* width, INT* height, void** data) const;

  
};

#endif
