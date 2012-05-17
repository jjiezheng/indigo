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
      LOG(LOG_CHANNEL_GL_UTILS, "error creating frame buffer");
    }
    
    switch (status) {
      case GL_FRAMEBUFFER_UNDEFINED:                      LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_UNDEFINED\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:          LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:  LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:         LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:         LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n"); break;
      case GL_FRAMEBUFFER_UNSUPPORTED:                    LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_UNSUPPORTED\n"); break;
      case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:         LOG(LOG_CHANNEL_GL_UTILS, "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n"); break;
      default: break;
    }
    
    assert(status == GL_FRAMEBUFFER_COMPLETE);
  }

  static
  void checkForError() {
    GLenum error = glGetError();
 
    if (error != GL_NO_ERROR) {
      const GLubyte * errorString = gluErrorString(error);
      LOG(LOG_CHANNEL_GL_UTILS, "%s", errorString);
    }
    
    assert(error == GL_NO_ERROR);
  }
  
};

#endif
