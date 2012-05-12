#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include "json/elements.h"

class Model;
class World;
class SceneContext;
class Material;

class WorldLoader {
  
public:
  
  void loadFromSceneFile(const std::string& filePath, World& world, SceneContext& sceneContext);
  
private:
  
  void loadSceneItem(const json::Object& objectItem, World& world);
  void loadModel(Model* model, const std::string& modelFilePath);
  void loadMaterial(Model* model, const std::string& materialFilePath);
  void loadShader(Material& material, const std::string& shaderFilePath);
  
};

#endif
