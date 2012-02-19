#ifndef CubeFX_Mesh_h
#define CubeFX_Mesh_h

#include "Standard.h"

class Shader;

class Mesh {
  
public:
  
  static Mesh* mesh(float* vertices, float* normals, int numVertices);
  
public:
  
  void render(Shader* shader) const;
  
  void setAmbient(float r, float g, float b);
  
  void setDiffuse(float r, float g, float b);
  
  void setSpecular(float r, float g, float b);
  
private:
  

  Mesh(float* vertices, float* normals, int numVertices);
  
  void init();
  
private:
  
  float* vertices_;
  float* normals_;
  int numVertices_;

  GLuint vertexArray;
  GLuint vertexBuffer;
  GLuint normalBuffer;  

  Color3 ambient_;
  Color3 diffuse_;
  Color3 specular_;

};

inline
void Mesh::setAmbient(float r, float g, float b) {
  ambient_.r = r;
  ambient_.g = g;
  ambient_.b = b;
}

inline
void Mesh::setDiffuse(float r, float g, float b) {
  diffuse_.r = r;
  diffuse_.g = g;
  diffuse_.b = b;
}

inline
void Mesh::setSpecular(float r, float g, float b) {
  specular_.r = r;
  specular_.g = g;
  specular_.b = b;
}


#endif
