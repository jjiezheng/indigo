#ifndef CubeFX_MaterialResource_h
#define CubeFX_MaterialResource_h

class TextureResource;

class MaterialResource {
  
public:
  
  MaterialResource(const glm::vec4& ambient, const glm::vec4& diffuse, const glm::vec4& specular, const std::deque<TextureResource*>& textures) 
  : ambient(ambient), diffuse(diffuse), specular(specular), textures(textures) { };
  
  glm::vec4 ambient;
  glm::vec4 diffuse;
  glm::vec4 specular;
  
  std::deque<TextureResource*> textures;
  
};

#endif
