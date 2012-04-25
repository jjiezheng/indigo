#ifndef CubeFX_File_h
#define CubeFX_File_h

#include <string>

class File {
  
public:
  
  File(const std::string& file_path)
    : file_path(file_path) { }
  
  std::string data();
    
private:
  
  std::string file_path;
  
};

#endif
