#ifndef ShaderCache_H_
#define ShaderCache_H_

#include <string>
#include <map>

class Shader;

class ShaderCache {
  
public:
  
  static ShaderCache* instance();
  
public:
  
  void init();
  
  Shader* addShader(const char* vertexPath, const char* fragmentPath);
  
private:
  
  std::map<std::string, Shader*> shaders_;
  
};

#endif
