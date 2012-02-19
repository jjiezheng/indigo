#ifndef ShadowMap_H_
#define ShadowMap_H_

#include <OpenGL/gl3.h>

class Light;
class Shader;

class ShadowMap {
  
public:
  
  void init();
  
  void begin(Light* light);
  
  void end();
  
  void debugDraw();
  
  void bind(Shader* shader);
  
private:
  
  GLuint shadowFrameBuffer_;
  GLuint shadowRenderDepthBuffer_;
  GLuint shadowRenderColorBuffer_;
  GLuint shadowTexture_;
  
  GLuint depthDebugVertArray_;
  GLuint depthDebugVertBuffer_;
  GLuint depthDebugUVBuffer_;
  
};

#endif
