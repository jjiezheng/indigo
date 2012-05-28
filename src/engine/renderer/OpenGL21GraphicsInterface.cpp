#include "OpenGL21GraphicsInterface.h"

#include "CGGLEffect.h"
#include "io/Log.h"
#include "Color3.h"
#include "VertexDefinition.h"

#include "OpenGL.h"
#include "ShaderSemantics.h"

#include <windows.h>
#include "platform/WindowsUtils.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "OpenGL.h"

#include "io/DDSImage.h"

#include "io/dds.h"
#include "io/DDSImage.h"
#include "io/DDSMipLevel.h"


HDC OpenGL21GraphicsInterface::createGraphicsContext(HWND hWnd, int width, int height) {
  static	PIXELFORMATDESCRIPTOR pixelFormatDescriptor =				// pfd Tells Windows How We Want Things To Be
  {
    sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
    1,											// Version Number
    PFD_DRAW_TO_WINDOW |						// Format Must Support Window
    PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
    PFD_DOUBLEBUFFER,							// Must Support Double Buffering
    PFD_TYPE_RGBA,								// Request An RGBA Format
    32,										    // Select Our Color Depth
    0, 0, 0, 0, 0, 0,							// Color Bits Ignored
    0,											// No Alpha Buffer
    0,											// Shift Bit Ignored
    0,											// No Accumulation Buffer
    0, 0, 0, 0,									// Accumulation Bits Ignored
    16,											// 16Bit Z-Buffer (Depth Buffer)  
    0,											// No Stencil Buffer
    0,											// No Auxiliary Buffer
    PFD_MAIN_PLANE,								// Main Drawing Layer
    0,											// Reserved
    0, 0, 0										// Layer Masks Ignored
  };

  HDC deviceContext = GetDC(hWnd);
  int pixelFormat = ChoosePixelFormat(deviceContext, &pixelFormatDescriptor);
  SetPixelFormat(deviceContext, pixelFormat, &pixelFormatDescriptor);

  HGLRC glResource = wglCreateContext(deviceContext);

  wglMakeCurrent(deviceContext, glResource);

  glViewport(0, 0, width, height);

  return deviceContext;
}

void OpenGL21GraphicsInterface::openWindow(int width, int height) {
  screenSize_ = CSize(width, height);
  HWND hWnd = WindowsUtils::createWindow(width, height);
  deviceContext_ = createGraphicsContext(hWnd, width, height);
  glewInit();
  CGGLEffect::initCG();
}

void OpenGL21GraphicsInterface::swapBuffers() {
  SwapBuffers(deviceContext_);
  windowClosed_ = WindowsUtils::pumpMessages();
}

int OpenGL21GraphicsInterface::createVertexBuffer(VertexDef* vertexData, int numVertices) {
  GLuint vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  {
    float vertexCoordsCount = numVertices * 3;
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

  float normalCoordsCount = numVertices * 3;
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
  
  float uvCoordsCount = numVertices * 2;
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

  return vertexArray;
}

void OpenGL21GraphicsInterface::drawVertexBuffer(int vertexBuffer, int vertexCount) {
  glBindVertexArray(vertexBuffer);
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

IEffect* OpenGL21GraphicsInterface::createEffect() {
  return new CGGLEffect();
}

void OpenGL21GraphicsInterface::clearBuffer(const Color3& color) {
  glClearColor(color.r, color.g, color.b, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL21GraphicsInterface::setPass(CGpass pass) {

}

bool OpenGL21GraphicsInterface::getKeySate(char key) {
  return false;//glfwGetKey(key) == GLFW_PRESS;
}

int OpenGL21GraphicsInterface::createTexture(const char* filePath) {
  DDSImage image;
  image.load(filePath);

  unsigned int format = 0;
  switch(image.fourCC) {
    case FOURCC_DXT1: format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT; break;
    case FOURCC_DXT3: format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT; break;
    case FOURCC_DXT5: format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT; break;
    default: return -1;
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

  return textureId;
}

void OpenGL21GraphicsInterface::setTexture(int textureId, CGparameter parameter) {

}
