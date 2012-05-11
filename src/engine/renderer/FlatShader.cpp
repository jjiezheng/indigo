#include "FlatShader.h"

#include "resource/ResourceCache.h"

#include "ShaderAttribs.h"

FlatShader* FlatShader::shader() {
  FlatShader* shader = new FlatShader();
  shader->init();
  return shader;
}

void FlatShader::init() {
  ShaderResource* resource = ResourceCache::instance()->load_shader("vmvp.vsh", "f.fsh");
  
  this->compile_vertex(resource->vertex_source());
  this->compile_fragment(resource->fragment_source());
  
  this->bind_attribute(ATTRIB_VERTEX, "vertex");
  
  this->link();
  
  this->add_uniform("model");
  this->add_uniform("view");
  this->add_uniform("projection");
}

void FlatShader::render() {  
  
}