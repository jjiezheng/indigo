#ifndef GLUtilities_H
#define GLUtilities_H

#include "OpenGL.h"
#include <assert.h> 
#include "io/Log.h"

class GLUtilities {
  
public:
  
  static void checkFramebufferStatus(int target) {
    GLenum status = glCheckFramebufferStatus(target);
    if (!status) return;

    if (status != GL_FRAMEBUFFER_COMPLETE) {
      LOG(LOG_CHANNEL_GL_UTILS, "error creating frame buffer");
    }

    switch(status) {
    case GL_FRAMEBUFFER_COMPLETE:
      return;
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
      LOG(LOG_CHANNEL_GL_UTILS, "An attachment could not be bound to frame buffer object!");
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
      LOG(LOG_CHANNEL_GL_UTILS, "Attachments are missing! At least one image (texture) must be bound to the frame buffer object!");
      break;

    /*case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
      LOG(LOG_CHANNEL_GL_UTILS, "The dimensions of the buffers attached to the currently used frame buffer object do not match!");
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
      LOG(LOG_CHANNEL_GL_UTILS, "The formats of the currently used frame buffer object are not supported or do not fit together!");
      break;*/

    case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
      LOG(LOG_CHANNEL_GL_UTILS, "A Draw buffer is incomplete or undefinied. All draw buffers must specify attachment points that have images attached.");
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
      LOG(LOG_CHANNEL_GL_UTILS, "A Read buffer is incomplete or undefinied. All read buffers must specify attachment points that have images attached.");
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
      LOG(LOG_CHANNEL_GL_UTILS, "All images must have the same number of multisample samples.");
      break;

    case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
      LOG(LOG_CHANNEL_GL_UTILS, "If a layered image is attached to one attachment, then all attachments must be layered attachments. The attached layers do not have to have the same number of layers, nor do the layers have to come from the same kind of texture.");
      break;

    case GL_FRAMEBUFFER_UNSUPPORTED:
      LOG(LOG_CHANNEL_GL_UTILS, "Attempt to use an unsupported format combinaton!");
      break;

    default:
      LOG(LOG_CHANNEL_GL_UTILS, "Unknown error while attempting to create frame buffer object!");
      break;
    }
    
    assert(status == GL_FRAMEBUFFER_COMPLETE);
  }

  static void checkForError() {
//#ifdef ADEBUG
    checkForGLError();
//    checkForCGError();
//#endif
  }

  static void checkForGLError() {
    GLenum error = glGetError();

    if (error != GL_NO_ERROR) {
      //const GLubyte * errorString = gluErrorString(error);
      //LOG(LOG_CHANNEL_GL_UTILS, "OpenGL Error: %s", errorString);
    }

    assert(error == GL_NO_ERROR);
  }

  static void getGLVersion(int* major, int* minor) {
    char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"

    *major = ver[0] - '0';
    if( *major >= 3) {
      glGetIntegerv(GL_MAJOR_VERSION, major); // major = 3
      glGetIntegerv(GL_MINOR_VERSION, minor); // minor = 2
    }
    else {
      *minor = ver[2] - '0';
    }

    ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION); // ver = "1.50 NVIDIA via Cg compiler"
  }  
};

#endif
