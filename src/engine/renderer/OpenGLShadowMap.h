#ifndef OPENGL_SHADOW_MAP_H
#define OPENGL_SHADOW_MAP_H

class OpenGLShadowMap {

public:

  OpenGLShadowMap(int shadowTextureId_, int depthBufferId_, int renderBufferId_)
    : shadowTextureId(shadowTextureId_)
    , depthBufferId(depthBufferId_)
    , renderBufferId(renderBufferId_) { }

public:

  int shadowTextureId;
  int depthBufferId;
  int renderBufferId;

};

#endif
