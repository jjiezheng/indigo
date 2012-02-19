#include "SkyBox.h"

#include "Model.h"
#include "ModelResource.h"

#include "ShaderResource.h"
#include "ShaderAttribs.h"
#include "Shader.h"

#include "Texture.h"
#include "TextureResource.h"
#include "ResourceCache.h"

SkyBox* SkyBox::skybox(const std::string& basename) {
  return new SkyBox(basename);
}

//void load_cube_face(GLenum position, TextureResource* texture_resource) {
//  glTexImage2D(position, 0, texture_resource->components(), texture_resource->width(), 
//               texture_resource->height(), 0, texture_resource->format(), GL_UNSIGNED_BYTE, 
//               texture_resource->data());  
//}
//

void SkyBox::init() { 
  
  
//  ModelResource* skybox_model_resource = ResourceCache::instance()->load_model("skybox.json");
//  model_ = Model::model(0, skybox_model_resource);
  
  ShaderResource* shader_resource = ResourceCache::instance()->load_shader("skybox.vsh", "skybox.fsh");
  shader_ = Shader::shader(shader_resource);
  
  shader_->bind_attribute(ATTRIB_VERTEX, "vertex");
  shader_->link();
  
  shader_->add_uniform("projection");
  shader_->add_uniform("view");
  shader_->add_uniform("model");
  
  
//  TextureResource* top = ResourceCache::instance()->load_texture(basename_ + "_top.png");
//  TextureResource* bottom = ResourceCache::instance()->load_texture(basename_ + "_bottom.png");
//  TextureResource* left = ResourceCache::instance()->load_texture(basename_ + "_left.png");
//  TextureResource* right = ResourceCache::instance()->load_texture(basename_ + "_right.png");
//  TextureResource* front = ResourceCache::instance()->load_texture(basename_ + "_front.png");
//  TextureResource* back = ResourceCache::instance()->load_texture(basename_ + "_back.png");
//  
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE); 
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
//  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//  
//  load_cube_face(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, top);
//  load_cube_face(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, bottom);
//  load_cube_face(GL_TEXTURE_CUBE_MAP_POSITIVE_X, left);
//  load_cube_face(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, right);
//  load_cube_face(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, front);
//  load_cube_face(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, back);
//  
//  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
  
}

void SkyBox::render(const MAT4& perspective) {
  shader_->use();
//  model_->render(*shader_, perspective);
}
