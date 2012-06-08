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
  void loadModel(Model* model, const std::string& modelFilePath);
  
private:
  
  void loadSceneItem(const json::Object& objectItem, World& world);
  void loadMaterial(Model* model, const std::string& materialFilePath);
  void loadEffect(Material& material, const std::string& shaderFilePath);
  
};

#endif
