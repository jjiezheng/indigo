#ifndef SKYBOX_H
#define SKYBOX_H
#include <string>

class IViewer;
class SceneContext;
class IEffect;

class SkyBox {
  
public:
  
  void load(const std::string& basename);
  
  void render(const IViewer* camera, const SceneContext& sceneContext) const;
  
private:
  
  void loadCubeSide(const std::string& filename, int direction);
  
private:
  
  IEffect* effect_;
  unsigned int vertexArray;
  unsigned int vertexBuffer;
  unsigned int cubeTexture_;
    
};

#endif
