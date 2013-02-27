#include "OpenGL32GraphicsInterface.h"

#include "OpenGLEffect.h"
#include "renderer/Color4.h"
#include "renderer/VertexDefinition.h"

#include "GLUtilities.h"

#include "OpenGL.h"
#include "OpenGLRenderTarget.h"
#include "renderer/ShaderSemantics.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"
#include "io/Log.h"

#include "GL/glfw.h"
#include "GRemdeyExtensions.h"

void OpenGL32GraphicsInterface::destroy() {
  glfwTerminate();
}

int OpenGL32GraphicsInterface::exitCode() const {
  return 0;
}

void OpenGL32GraphicsInterface::openWindow(int width, int height, unsigned int multiSamples) {
  int result = glfwInit();

  if (!result) {
    LOG(LOG_CHANNEL_RENDERER, "Failed to init GLFW");
  }
  
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);

#ifdef PLATFORM_LINUX
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);
#endif

#ifdef PLATFORM_MAC
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  
  glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  
  result = glfwOpenWindow(width, height, 8, 8, 8, 8, 0, 0, GLFW_WINDOW);
  
  if (!result) {
    LOG(LOG_CHANNEL_RENDERER, "Failed to open window");
  }

  GLUtilities::checkForError();
  
  initGremedyExtension();
  
  backbufferSize_.width = width;
  backbufferSize_.height = height;
  
  screenSize_.width = width;
  screenSize_.height = height;
  
  depthBufferTexture_ = createDepthTexture(screenSize_, false);
  depthBufferTarget_ = createRenderTarget(depthBufferTexture_);
}

void OpenGL32GraphicsInterface::setViewport(const CSize& dimensions) {
  glViewport(0, 0, dimensions.width, dimensions.height);
}

void OpenGL32GraphicsInterface::beginPerformanceEvent(const std::string& eventName) {

  if (NULL != glStringMarkerGREMEDY) {
    performanceEventStack_.push(eventName);
    std::string output;
    output += "########## Start ";
    output += eventName;
    output += " ##########";
    glStringMarkerGREMEDY(output.length(), output.c_str());

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      glStringMarkerGREMEDY = NULL;
    }

    GLUtilities::checkForError();
  }
}

void OpenGL32GraphicsInterface::endPerformanceEvent() {
  if (NULL != glStringMarkerGREMEDY) {
    std::string eventName = performanceEventStack_.top();
    performanceEventStack_.pop();
    std::string output;
    output += "########## End ";
    output += eventName;
    output += " ##########";
    glStringMarkerGREMEDY(output.length(), output.c_str());
    GLUtilities::checkForError();
  }
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
    uvs[uvi++] = 1.0f - vertexData[i].uv.y;
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
  GLUtilities::checkForError();
}

void OpenGL32GraphicsInterface::clearActiveRenderTargets(const Color4& color) {
  glClearColor(color.r, color.g, color.b, color.a);
  glClear(GL_COLOR_BUFFER_BIT);
}

IEffect* OpenGL32GraphicsInterface::createEffect() {
  return new OpenGLEffect();
}

void OpenGL32GraphicsInterface::resetGraphicsState(bool cullBack) {
  glEnable(GL_CULL_FACE);
  
  int faceToCull = cullBack ? GL_BACK : GL_FRONT;
  glCullFace(faceToCull);
  GLUtilities::checkForError();

  //  glEnable(GL_POLYGON_OFFSET_FILL);
  //  glPolygonOffset(2.5f, 10.0f);
}

void OpenGL32GraphicsInterface::enableSmoothing() {
  
}

void OpenGL32GraphicsInterface::disableSmoothing() {
  
}

unsigned int OpenGL32GraphicsInterface::loadTexture(const std::string& filePath) {
  DDSImage dds;
  dds.load(filePath);
  
  GLuint textureId = 0;
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  
  GLuint format = 0;
  
  switch(dds.fourCC) {
    case FOURCC_DXT1:
      format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      break;
    case FOURCC_DXT3:
      format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      break;
    case FOURCC_DXT5:
      format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      break;
    default:
      assert(false);
  }
  
  for (int i = 0; i < dds.numMipLevels; i++) {
    DDSMipLevel* mipLevel = dds.mipLevels[i];
    glCompressedTexImage2D(GL_TEXTURE_2D, i, format, mipLevel->width, mipLevel->height, 0, mipLevel->size, dds.data + mipLevel->offset);
    GLUtilities::checkForError();
  }
  
  return textureId;
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
      openGLTextureFormat = GL_RGBA32F;
      break;
    }
  }
  
  glTexImage2D(GL_TEXTURE_2D, 0, openGLTextureFormat, dimensions.width, dimensions.height, 0, GL_RGBA, GL_FLOAT, textureData);// GL_UNSIGNED_BYTE, textureData);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  
  return textureId;
}

void OpenGL32GraphicsInterface::generateMipMaps(unsigned int textureId) {
  
}

void OpenGL32GraphicsInterface::fillTexture(unsigned int textureId, void* data, unsigned int dataSize) {
  
}

void OpenGL32GraphicsInterface::setRenderTarget(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, const CSize& dimensions, unsigned int depthTextureId) {
  
}

unsigned int OpenGL32GraphicsInterface::createFrameBuffer(unsigned int* renderTargetIds, unsigned int renderTargetCount, bool useDepthBuffer, unsigned int depthBufferTargetId) {
  GLuint frameBufferId = 0;
  glGenFramebuffers(1, &frameBufferId);
  GLUtilities::checkForError();
  
  glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
  
  GLuint drawBuffers[renderTargetCount];
  
  for (unsigned int i = 0; i < renderTargetCount; i++) {
    GLuint renderTargetId = renderTargetIds[i];
    GLuint textureId = renderTargetTextures_[renderTargetId];

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, textureId, 0);
    GLUtilities::checkForError();
    
    drawBuffers[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  
  if (useDepthBuffer) {
    glEnable(GL_DEPTH_TEST);
    unsigned int depthTextureId = renderTargetTextures_[depthBufferTargetId];
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTextureId, 0);
    GLUtilities::checkForError();
  } else {
    glDisable(GL_DEPTH_TEST);
  }
  
  glDrawBuffers(renderTargetCount, (GLenum*)drawBuffers);
  GLUtilities::checkForError();
  GLUtilities::checkFramebufferStatus(GL_FRAMEBUFFER);

  return frameBufferId;
}

void OpenGL32GraphicsInterface::setFrameBuffer(unsigned int frameBufferId) {
  glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);
  GLUtilities::checkForError();
}

void OpenGL32GraphicsInterface::resetRenderTarget(bool useDepthBuffer) {
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  GLUtilities::checkForError();

  if (useDepthBuffer) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}

unsigned int OpenGL32GraphicsInterface::createRenderTarget(unsigned int textureId) {
  unsigned int renderTargetId = renderTargetTextures_.size();
  renderTargetTextures_.push_back(textureId);
  return renderTargetId;
}

void OpenGL32GraphicsInterface::clearRenderTarget(unsigned int renderTargetId, const Color4& color) {
  
}

unsigned int OpenGL32GraphicsInterface::createDepthTexture(const CSize& dimensions, bool isShadowTexture) {
  GLuint depthBufferTexture = 0;
  glGenTextures(1, &depthBufferTexture);
  glBindTexture(GL_TEXTURE_2D, depthBufferTexture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, dimensions.width, dimensions.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
  
  if (isShadowTexture) {
    GLfloat v_bc[] = {1.0f,1.0f,1.0f,1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, v_bc);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  }

  GLUtilities::checkForError();
  return depthBufferTexture;
}

void OpenGL32GraphicsInterface::clearActiveDepthBuffer(unsigned int textureId) {
  glClear(GL_DEPTH_BUFFER_BIT);
}

unsigned int OpenGL32GraphicsInterface::depthBufferTexture() const {
  return depthBufferTexture_;
}

unsigned int OpenGL32GraphicsInterface::depthBufferTarget() const {
  return depthBufferTarget_;
}

void OpenGL32GraphicsInterface::setBlendState(IGraphicsInterface::BlendState blendState) {
  switch (blendState) {
    case ALPHA: {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      break;
    }
    case ADDITIVE: {
      glEnable(GL_BLEND);
      glBlendFunc(GL_ONE, GL_ONE);
      break;
    }
    case NOBLEND: {
      glDisable(GL_BLEND);
      glBlendFunc(GL_ONE, GL_ONE);
      break;
    }
  }
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
  glBindTexture(GL_TEXTURE_2D, textureId);
  TextureInfo textureInfo;
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, (GLint*)&textureInfo.width);
  glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, (GLint*)&textureInfo.height);
  return textureInfo;
}


