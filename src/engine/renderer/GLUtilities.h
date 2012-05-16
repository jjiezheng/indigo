#ifndef GLUtilities_H
#define GLUtilities_H

#include "OpenGL.h"
#include <assert.h>

class GLUtilities {
  
public:
  
  static
  void checkFramebufferStatus(int target) {
    GLenum status = glCheckFramebufferStatus(target);
    if (status != GL_FRAMEBUFFER_COMPLETE) {
      printf("error creating frame buffer\n");
    }
    
    switch (status) {
      case GL_FRAMEBUFFER_UNDEFINED: printf("GL_FRAMEBUFFER_UNDEFINED\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: printf("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: printf("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: printf("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: printf("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n"); break;
      case GL_FRAMEBUFFER_UNSUPPORTED: printf("GL_FRAMEBUFFER_UNSUPPORTED\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: printf("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n"); break;
      default: break;
    }
  }

  static
  void checkForError() {
    GLenum error = glGetError();
 
    if (error != GL_NO_ERROR) {
      const GLubyte * errorString = glGetString(error);
      printf("%s", errorString);
    }
    assert(error == GL_NO_ERROR);
  }
  
};

#endif
