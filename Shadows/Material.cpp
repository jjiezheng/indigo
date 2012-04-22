#include "Material.h"

Material* Material::material(Shader* shader) {
  return new Material(shader);
}

Material::Material(Shader* shader)
  : shader_(shader) {
  
}