#include "OpenGL21GraphicsInterface.h"

#include "renderer/CGGLEffect.h"
#include "io/Log.h"
#include "renderer/Color3.h"

#include "renderer/OpenGL.h"
#include "renderer/ShaderAttribs.h"

#include <windows.h>
#include "platform/WindowsUtils.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>

#include "OpenGL.h"

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

int OpenGL21GraphicsInterface::createVertexBuffer(float* vertices, float* normals, float* uvs, int numVertices) {
  GLuint vertexArray;
  glGenVertexArrays(1, &vertexArray);
  glBindVertexArray(vertexArray);

  GLuint vertexBuffer;  
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, vertices, GL_STATIC_DRAW);  
  glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_VERTEX);
  
  GLuint normalBuffer;
  glGenBuffers(1, &normalBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
  glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * numVertices, normals, GL_STATIC_DRAW);    
  glVertexAttribPointer(ATTRIB_NORMAL, 3, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_NORMAL);
  
  GLuint uvBuffer;
  glGenBuffers(1, &uvBuffer); 
  glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
  glBufferData(GL_ARRAY_BUFFER, 2 * sizeof(float) * numVertices, uvs, GL_STATIC_DRAW);
  glVertexAttribPointer(ATTRIB_UV, 2, GL_FLOAT, 0, 0, 0);
  glEnableVertexAttribArray(ATTRIB_UV);

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
  return glfwGetKey(key) == GLFW_PRESS;
}
