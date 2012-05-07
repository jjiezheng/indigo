#ifndef SKYBOX_H
#define SKYBOX_H

#include "Shader.h"

class IViewer;
class SceneContext;

class SkyBox {
  
public:
  
  void load(const std::string& basename);
  
  void render(const IViewer* camera, const SceneContext& sceneContext) const;
  
private:
  
  Shader shader_;
  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint cubeTexture_;
    
};

#endif
