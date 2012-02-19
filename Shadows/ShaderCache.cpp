#include "ShaderCache.h"

#include <string>
#include <sstream>
#include <iostream>

#include "ResourceCache.h"
#include "Shader.h"

#include "ShaderCache.h"
#include "Shader.h"
#include "ShaderAttribs.h"

static ShaderCache* instance_ = nullptr;

ShaderCache* ShaderCache::instance() {
  if (!instance_) {
    instance_ = new ShaderCache();
    instance_->init();
  }
  return instance_;
}

void ShaderCache::init() {
  {
    Shader* shader = instance()->addShader("v.vsh", "f.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
  }
  
  {
    Shader* shader = instance()->addShader("v.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("projection");
  }
  
  {
    Shader* shader = instance()->addShader("vp.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("projection");
  }
  
  {
    Shader* shader = instance()->addShader("vm.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("model");
  }
  
  {
    Shader* shader = instance()->addShader("vmp.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("projection");
  }
    
  {
    Shader* shader = instance()->addShader("vmvp.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
  }
  
  {
    Shader* shader = instance()->addShader("vmvps.vsh", "fcs.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
    shader->add_uniform("lightMatrix");
    shader->add_uniform("shadowMapTexture");
  }

  {
    Shader* shader = instance()->addShader("vmvpc.vsh", "fcl.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_NORMAL, "normal");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
    
    shader->add_uniform("lightPositions");
    shader->add_uniform("numLights");
    shader->add_uniform("normalMatrix");
    
    shader->add_uniform("ambient");
    shader->add_uniform("diffuse");
    shader->add_uniform("specular");
  }
  
  {
    Shader* shader = instance()->addShader("vmvpcs.vsh", "fcls.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_NORMAL, "normal");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
    
    shader->add_uniform("lightPositions");
    shader->add_uniform("numLights");
    shader->add_uniform("normalMatrix");
    
    shader->add_uniform("ambient");
    shader->add_uniform("diffuse");
    shader->add_uniform("specular");
    
    shader->add_uniform("lightMatrix");
    shader->add_uniform("shadowMapTexture");
  }

  
  {
    Shader* shader = instance()->addShader("vmvpc.vsh", "fc.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_NORMAL, "normal");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
    
    shader->add_uniform("ambient");
    shader->add_uniform("diffuse");
    shader->add_uniform("specular");
  }

  
  {
    Shader* shader = instance()->addShader("vmpt.vsh", "ft.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_UV, "textureCoords");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("projection");
    shader->add_uniform("colorMap");
  }
  
  {
    Shader* shader = instance()->addShader("vt.vsh", "ft.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_UV, "textureCoords");
    shader->link();
    shader->add_uniform("colorMap");
  }
  
  {
    Shader* shader = instance()->addShader("vmvpt.vsh", "ft.fsh");
    shader->bind_attribute(ATTRIB_VERTEX, "vertex");
    shader->bind_attribute(ATTRIB_UV, "textureCoords");
    shader->link();
    shader->add_uniform("model");
    shader->add_uniform("view");
    shader->add_uniform("projection");
    shader->add_uniform("colorMap");
  }
}

Shader* ShaderCache::addShader(const char *vertexPath, const char *fragmentPath) {  
  std::stringstream keyStream;
  keyStream << vertexPath << "_" << fragmentPath;
  std::string key = keyStream.str();

  Shader* shader = nullptr;
    
  if (shaders_.find(key) != shaders_.end()) {
    shader = shaders_[key];
  } else {
    std::clog << "loading shader pair: " << key << std::endl;
    ShaderResource* shaderResource = ResourceCache::instance()->load_shader(vertexPath, fragmentPath);
    shader = Shader::shader(shaderResource);
    shaders_[key] = shader;
    
    shader->compile_vertex(shaderResource->vertex_source());
    shader->compile_fragment(shaderResource->fragment_source());
  }
  
  return shader;
}

