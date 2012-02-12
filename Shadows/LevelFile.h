#ifndef CubeFX_LevelFile_h
#define CubeFX_LevelFile_h

#include "Standard.h"

//#include "EntityComponent.h"

class LevelResource;
class SkyBox;

class LevelFile {
  
public:
  
  static LevelFile* level_file(LevelResource* level_resource);
  
  LevelFile(LevelResource* level_resource)
    : level_resource_(level_resource) 
  { 
  
  };
  
//  std::deque<EntityComponent*> components();
  
  SkyBox* skybox();
  
private:
  
  std::string file_path;
  LevelResource* level_resource_;
  
};

#endif
