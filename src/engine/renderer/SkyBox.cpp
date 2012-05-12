#include "SkyBox.h"

#include "io/Image.h"
#include "core/String.h"
#include "maths/Matrix4x4.h"
#include "maths/Vector4.h"

#include "ShaderAttribs.h"
#include "IViewer.h"
#include "SceneContext.h"

static const int NUM_VERTICES = 36;

void SkyBox::loadCubeSide(const std::string& filename, GLint direction) {
  Image* image = Image::imageFromFile(filename);
  glTexImage2D(direction, 0, image->components(), image->width(), 
               image->height(), 0, image->format(), GL_UNSIGNED_BYTE, image->data());
}

void SkyBox::load(const std::string& basename) {
  {
    glGenTextures(1, &cubeTexture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture_);
  }
  {
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    String basenameString(basename);
    String extension = basenameString.pathExtension();
    String filename = basenameString.removePathExtension();
    
    std::string topFileName = (filename + "_top" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
    
    std::string bottomFileName = (filename + "_bottom" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);

    std::string leftFileName = (filename + "_left" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_X);
    
    std::string rightFileName = (filename + "_right" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
    
    std::string frontFileName = (filename + "_front" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
    
    std::string backFileName = (filename + "_back" + extension).str();
    loadCubeSide(topFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
    
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  }
  {
    shader_.load("skybox_fog.vsh", "skybox_fog.fsh");
    shader_.bind_attribute(ATTRIB_VERTEX, "vertex");
    shader_.link();
    
    shader_.add_uniform("projection");
    shader_.add_uniform("view");
    shader_.add_uniform("model");
    shader_.add_uniform("cubeMap");
    
    shader_.add_uniform("fogStart");
    shader_.add_uniform("fogEnd");
    shader_.add_uniform("fogColor");
    shader_.add_uniform("fogType");
    shader_.add_uniform("fogFactor");
  }
  
    float vertices[108] = { 
      1, 1, -1,
      -1, 1, -1,
      -1, -1, -1,
      -1, -1, -1,
      1, -1, -1,
      1, 1, -1,
      
      1, 1, 1,
      1, -1, 1,
      -1, -1, 1,
      -1, -1, 1,
      -1, 1, 1,
      1, 1, 1,
      
      1, 1, -1,
      1, -1, -1,
      1, -1, 1,
      1, -1, 1,
      1, 1, 1, 
      1, 1, -1,
      
      1, -1, -1,
      -1, -1, -1,
      -1, -1, 1,
      -1, -1, 1,
      1, -1, 1,
      1, -1, -1,
      
      -1, -1, -1,
      -1, 1, -1,
      -1, 1, 1,
      -1, 1, 1,
      -1, -1, 1,
      -1, -1, -1,
      
      -1, 1, -1,
      1, 1, -1,
      1, 1, 1,
      1, 1, 1,
      -1, 1, 1,
      -1, 1, -1
    };
        
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);
    
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * NUM_VERTICES, vertices, GL_STATIC_DRAW);  
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, 0, 0, 0);
    glEnableVertexAttribArray(ATTRIB_VERTEX);    
}

void SkyBox::render(const IViewer* camera, const SceneContext& sceneContext) const {
  shader_.use();
  
  shader_.set_uniform(camera->projection(), "projection");
  shader_.set_uniform(camera->viewTransform(), "view");
 
  Matrix4x4 scale = Matrix4x4::scale(100);
  Matrix4x4 translation = Matrix4x4::translation(camera->position());
  Matrix4x4 model = translation   * scale;
  
  shader_.set_uniform(model, "model");
  
  glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture_);
  shader_.set_uniform(0, "cubeMap");
  
  shader_.set_uniform(sceneContext.fogStart(), "fogStart");
  shader_.set_uniform(sceneContext.fogEnd(), "fogEnd");
  shader_.set_uniform(sceneContext.fogColor(), "fogColor");
  shader_.set_uniform(sceneContext.fogType(), "fogType");
  shader_.set_uniform(sceneContext.fogFactor(), "fogFactor");
  
  glBindVertexArray(vertexArray);
  glDrawArrays(GL_TRIANGLES, 0, NUM_VERTICES);
}