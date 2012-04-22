#ifndef CubeFX_Mesh_h
#define CubeFX_Mesh_h

#include "Standard.h"

#include "Color3.h"
#include "SceneNode.h"

class Shader;
class Material;

class Mesh : public SceneNode {
  
public:
  
  static Mesh* mesh(float* vertices, float* normals, int numVertices, Material* material);
  
public:
  
  void render(Shader* shader) const;
  
  void queueRender(Renderer* renderer);
  
  Material* material() const;
    
private:
  
  Mesh(float* vertices, float* normals, int numVertices, Material* material);
  
  void init();
  
private:
  
  float* vertices_;
  float* normals_;
  int numVertices_;

  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint normalBuffer;  
  
  Material* material_;
};

inline
Material* Mesh::material() const {
  return material_;
}

#endif
