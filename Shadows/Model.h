#ifndef CubeFX_Model_h
#define CubeFX_Model_h

#include "SceneNode.h"
#include <deque>

class Mesh;
class Camera;

class Model : public SceneNode {
  
public:
  
  static Model* model(const char* filepath);
  
public:
  
  void render(Renderer* renderer);
  
  void render(Shader* shader) const;
  
private:
  
  Model() = default;
  
private:
  
  void load(const char* filepath);
  
private:
  
  std::deque<Mesh*> meshes_;
  
};

#endif
