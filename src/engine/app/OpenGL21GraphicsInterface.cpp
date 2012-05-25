#include "OpenGL21GraphicsInterface.h"

#include "renderer/CGGLEffect.h"
#include "io/Log.h"
#include "renderer/Color3.h"

#include "renderer/OpenGL.h"
#include "renderer/ShaderAttribs.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>


void OpenGL21GraphicsInterface::openWindow( int width, int height ) {

}

void OpenGL21GraphicsInterface::swapBuffers() {
  
}

bool OpenGL21GraphicsInterface::windowClosed() const {
  return windowClosed_;
}

int OpenGL21GraphicsInterface::exitCode() const {
  return exitCode_;
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
