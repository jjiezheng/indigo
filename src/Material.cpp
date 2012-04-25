#include "Material.h"

#include "Texture.h"

#include "Shader.h"

Material* Material::material(Shader* shader) {
  return new Material(shader);
}

Material::Material(Shader* shader)
  : shader_(shader) {
  
}

void Material::render(Shader* shader) {
  shader->render();
}