#ifndef OPENGL_SHADOW_MAP_H
#define OPENGL_SHADOW_MAP_H

class OpenGLShadowMap {

public:

  OpenGLShadowMap(int shadowTextureId_, int frameBufferId_, int renderBufferId_)
    : shadowTextureId(shadowTextureId_)
    , frameBufferId(frameBufferId_)
    , renderBufferId(renderBufferId_) { }

public:

  int shadowTextureId;
  int frameBufferId;
  int renderBufferId;

};

#endif
