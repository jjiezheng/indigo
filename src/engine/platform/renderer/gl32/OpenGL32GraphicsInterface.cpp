#include "OpenGL32GraphicsInterface.h"

#include "OpenGLEffect.h"
#include "Color4.h"
#include "VertexDefinition.h"

#include "GLUtilities.h"

#include "OpenGL.h"
#include "OpenGLRenderTarget.h"
#include "ShaderSemantics.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"
#include "io/Log.h"

#include "GL/glfw.h"

void OpenGL32GraphicsInterface::destroy() {
  glfwTerminate();
}

bool OpenGL32GraphicsInterface::windowClosed() const {
  return false;
}

int OpenGL32GraphicsInterface::exitCode() const {
  return 0;
}


void OpenGL32GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  glfwInit();
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);
  
  backbufferSize_.width = width;
  backbufferSize_.height = height;
  
  screenSize_.width = width;
  screenSize_.height = height;
  
}

void OpenGL32GraphicsInterface::setViewport(const CSize& dimensions) {
  glViewport(0, 0, dimensions.width, dimensions.height);
}

void OpenGL32GraphicsInterface::beginPerformanceEvent(const std::string& eventName) {
  
}

void OpenGL32GraphicsInterface::endPerformanceEvent() {
  
}

void OpenGL32GraphicsInterface::swapBuffers() {
  glfwSwapBuffers();
  
  windowClosed_ = !glfwGetWindowParam(GLFW_OPENED);
}

unsigned int OpenGL32GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  
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
  
  GLUtilities::checkForError();
  
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
  
  GLUtilities::checkForError();
  
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

void OpenGL32GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount, VertexFormat vertexFormat) {
  glBindVertexArray(vertexBuffer);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

void OpenGL32GraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

IEffect* OpenGL32GraphicsInterface::createEffect() {
  return new OpenGLEffect();
}

void OpenGL32GraphicsInterface::resetGraphicsState(bool cullBack) {
//  glEnable(GL_DEPTH_TEST);
//  glEnable(GL_CULL_FACE);
  
//  glPolygonOffset(2.5f, 10.0f);
//  glEnable(GL_POLYGON_OFFSET_FILL);
  
//  int faceToCull = cullBack ? GL_BACK : GL_FRONT;
//  glCullFace(faceToCull);
//  GLUtilities::checkForError();
//  glCullFace(GL_BACK);
}

void OpenGL32GraphicsInterface::enableSmoothing() {
  
}

void OpenGL32GraphicsInterface::disableSmoothing() {
  
}

unsigned int OpenGL32GraphicsInterface::loadTexture(const std::string& filePath) {
  return 0;
}

unsigned int OpenGL32GraphicsInterface::createTexture(const CSize& dimensions, TextureFormat textureFormat, unsigned int multisamples, unsigned int mipLevels, void* textureData, unsigned int textureLineSize, bool isDynamic) {
  GLuint textureId = 0;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  
  GLuint openGLTextureFormat = GL_RGBA;
  
  switch (textureFormat) {
    case IGraphicsInterface::R8G8B8A8: {
      openGLTextureFormat = GL_RGBA8;
      break;
    }
    case IGraphicsInterface::R16G16B16A16: {
      openGLTextureFormat = GL_RGBA16;
      break;
    }
    case IGraphicsInterface::R16G16: {
      openGLTextureFormat = GL_RG16;
      break;
    }
    case IGraphicsInterface::R32G32B32A32: {
      openGLTextureFormat = GL_RGBA;
      break;
    }
  }
  
  glTexImage2D(GL_TEXTURE_2D, 0, openGLTextureFormat, dimensions.width, dimensions.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
  
  return textureId;
}

void OpenGL32GraphicsInterface::generateMipMaps(unsigned int textureId) {
  
}

void OpenGL32GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {
  
}

void OpenGL32GraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  GLuint frameBufferId = 0;
  glGenFramebuffers(1, &frameBufferId);
  GLUtilities::checkForError();
  
  glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
  
  GLuint drawBuffers[renderTargetCount];
  
  for (unsigned int i = 0; i < renderTargetCount; i++) {
    GLuint renderTargetId = renderTargetIds[i];

    glBindRenderbuffer(GL_RENDERBUFFER, renderTargetId);
    GLUtilities::checkForError();
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_RENDERBUFFER, renderTargetId);
    GLUtilities::checkForError();
    
    GLuint textureId = renderBufferTextures_[renderTargetId];
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textureId, 0);
    GLUtilities::checkForError();
    
    drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  
  glDrawBuffers(renderTargetCount, drawBuffers);
  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);
}

void OpenGL32GraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  GLUtilities::checkForError();
}

unsigned int OpenGL32GraphicsInterface::createRenderTarget(unsigned int textureId) {
  GLuint renderBufferId = 0;
  glGenRenderbuffers(1, &renderBufferId);
  
  GLUtilities::checkForError();
  
  GLint width = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
  
  GLint height = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

  GLint internalFormat = 0;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &internalFormat);

  glBindRenderbuffer(GL_RENDERBUFFER, renderBufferId);
  glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
  
  GLUtilities::checkForError();
  
  renderBufferTextures_[renderBufferId] = textureId;

  return renderBufferId;
}

void OpenGL32GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  
}

unsigned int OpenGL32GraphicsInterface::createDepthTexture(const CSize& dimensions) {
  return 0;
}

void OpenGL32GraphicsInterface::clearActiveDepthBuffer(unsigned int textureId) {
  
}

unsigned int OpenGL32GraphicsInterface::depthBufferTexture() const {
  return 0;
}

void OpenGL32GraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  
}

Vector2 OpenGL32GraphicsInterface::halfBackBufferPixel() const {
  return Vector2();
}

Vector2 OpenGL32GraphicsInterface::halfScreenPixel() const {
  return Vector2();
}

void OpenGL32GraphicsInterface::setTextureData(unsigned int textureId, const void* textureData, const CSize& textureDimensions, unsigned int texturePitch) {
  
}

TextureInfo OpenGL32GraphicsInterface::textureInfo(unsigned int textureId) {
  return TextureInfo();
}


