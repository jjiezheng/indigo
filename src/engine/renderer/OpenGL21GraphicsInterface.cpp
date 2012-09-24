#include "OpenGL21GraphicsInterface.h"

#include "CGGLEffect.h"
#include "io/Log.h"
#include "Color4.h"
#include "VertexDefinition.h"

#include "OpenGL.h"
#include "OpenGLRenderTarget.h"
#include "GLUtilities.h"
#include "ShaderSemantics.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "io/DDSImage.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"


void OpenGL21GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  screenSize_ = CSize(width, height);
  
  CGGLEffect::initCG();
}

void OpenGL21GraphicsInterface::swapBuffers() {
  windowClosed_ = false;
}

unsigned int OpenGL21GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  GLuint vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  {
    unsigned int vertexCoordsCount = numVertices * 3;
    float* vertices = new float[vertexCoordsCount];
    int vertexi = 0;
    for (int i = 0; i < numVertices; i++) {
      vertices[vertexi++] = vertexData[i].vertex.x;
      vertices[vertexi++] = vertexData[i].vertex.y;
      vertices[vertexi++] = vertexData[i].vertex.z;
    }

    GLuint vertexBuffer;  
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);  
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(POSITION);

    delete[] vertices;
  }

  unsigned int normalCoordsCount = numVertices * 3;
  float* normals = new float[normalCoordsCount];
  int normali = 0;
  for (int i = 0; i < numVertices; i++) {
    normals[normali++] = vertexData[i].normal.x;
    normals[normali++] = vertexData[i].normal.y;
    normals[normali++] = vertexData[i].normal.z;
  }

  GLuint normalBuffer;
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, normals, GL_STATIC_DRAW);    
  glVertexAttribPointer(NORMAL, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(NORMAL);

  delete[] normals;
  
  unsigned int uvCoordsCount = numVertices * 2;
  float* uvs = new float[uvCoordsCount];
  int uvi = 0;
  for (int i = 0; i < numVertices; i++) {
    uvs[uvi++] = vertexData[i].uv.x;
    uvs[uvi++] = vertexData[i].uv.y;
  }
  
  GLuint uvBuffer;
  glGenBuffers(1, &uvBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * numVertices, uvs, GL_STATIC_DRAW);
  glVertexAttribPointer(TEXCOORD0, 2, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(TEXCOORD0);

  delete[] uvs;

  GLUtilities::checkForError();

  return vertexArray;
}

void OpenGL21GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  glBindVertexArray(vertexBuffer);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

IEffect* OpenGL21GraphicsInterface::createEffect() {
  return new CGGLEffect();
}

void OpenGL21GraphicsInterface::clearBuffer(const Color4& color) {
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GLUtilities::checkForError();
}

bool OpenGL21GraphicsInterface::getKeySate(char key) {
  return false;
}

unsigned int OpenGL21GraphicsInterface::loadTexture(const std::string& filePath) {
  DDSImage image;
  image.load(filePath.c_str());

  unsigned int format = 0;
  switch(image.fourCC) {
    case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
    case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
    case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
    default: return 0;
  }

  GLuint textureId;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, image.numMipLevels - 1);

  for (unsigned int i = 0; i < image.numMipLevels; i++) {
    DDSMipLevel* mipLevel = image.mipLevels[i];
    glCompressedTexImage2D(GL_TEXTURE_2D, i, format, mipLevel->width, mipLevel->height, 
                           0, mipLevel->size, image.data + mipLevel->offset);
  }

  GLUtilities::checkForError();

  return textureId;
}

void OpenGL21GraphicsInterface::resetGraphicsState(bool cullBack) {
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  glPolygonOffset(2.5f, 10.0f);
  glEnable(GL_POLYGON_OFFSET_FILL);
 
  int faceToCull = cullBack ? GL_BACK : GL_FRONT;
  glCullFace(faceToCull);
  GLUtilities::checkForError();
}

unsigned int OpenGL21GraphicsInterface::createTexture(const CSize& dimensions, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize) {
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, dimensions.width, dimensions.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  GLUtilities::checkForError();
  glBindTexture(GL_TEXTURE_2D, 0);
  return texture;
}

void OpenGL21GraphicsInterface::setRenderTarget(unsigned int* renderBuffers, unsigned int renderTargetCount, bool useDepthBuffer) {
  
  unsigned int primartyRenderTargetId = renderBuffers[0];
  OpenGLRenderTarget primaryRenderTarget = renderTargets_[primartyRenderTargetId];
  glBindFramebuffer(GL_FRAMEBUFFER, primaryRenderTarget.frameBuffer);

  for (unsigned int i = 0; i < renderTargetCount; i++) {
    unsigned int renderBuffer = renderBuffers[i];
    OpenGLRenderTarget renderTarget = renderTargets_[renderBuffer];
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, renderTarget.renderBuffer);
    GLUtilities::checkForError();
  }
}

unsigned int OpenGL21GraphicsInterface::createRenderTarget(unsigned int textureId) {
  GLuint frameBuffer = 0;
  glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
  GLUtilities::checkForError();

  //--

  GLuint colorRenderBuffer = 0;
  glGenRenderbuffers(1, &colorRenderBuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, colorRenderBuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_RGBA, screenSize_.width, screenSize_.height);
  GLUtilities::checkForError();

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderBuffer);
  GLUtilities::checkForError();

  //--

  /*GLuint depthRenderbuffer;
  glGenRenderbuffers(1, &depthRenderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, screenSize_.width, screenSize_.height);
  
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbuffer);
  GLUtilities::checkForError();*/

  //--

  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);

  //--

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
  GLUtilities::checkForError();

  //--

  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  GLUtilities::checkForError();

  unsigned int rendetTargetId = (unsigned int)renderTargets_.size();
  OpenGLRenderTarget renderTarget;
  renderTarget.renderBuffer = colorRenderBuffer;
  renderTarget.frameBuffer = frameBuffer;
  renderTargets_.push_back(renderTarget);
  return rendetTargetId;
}

void OpenGL21GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  OpenGLRenderTarget renderTarget = renderTargets_[renderTargetId];
  glBindFramebuffer(GL_FRAMEBUFFER, renderTarget.frameBuffer);
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  GLUtilities::checkForError();
}

void OpenGL21GraphicsInterface::resetRenderTarget() {
  glCullFace(GL_BACK);
  glDisable(GL_POLYGON_OFFSET_FILL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_TEXTURE_2D);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  GLUtilities::checkForError();
}

void OpenGL21GraphicsInterface::generateMipMaps(unsigned int textureId) {

}

void OpenGL21GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {

}

void OpenGL21GraphicsInterface::beginPerformanceEvent(const std::string& eventName, const Color4& color) {

}

void OpenGL21GraphicsInterface::endPerformanceEvent() {

}

void OpenGL21GraphicsInterface::getMousePosition(int* x, int* y) {

}
