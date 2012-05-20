#ifndef SKYBOX_H
#define SKYBOX_H

#include "Effect.h"
#include "OpenGL.h"

class IViewer;
class SceneContext;

class SkyBox {
  
public:
  
  void load(const std::string& basename);
  
  void render(const IViewer* camera, const SceneContext& sceneContext) const;
  
private:
  
  void loadCubeSide(const std::string& filename, GLint direction);
  
private:
  
  Effect effect_;
  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint cubeTexture_;
    
};

#endif
