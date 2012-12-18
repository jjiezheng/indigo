#ifndef WORLDLOADER_H
#define WORLDLOADER_H

#include "json/elements.h"

#include "Material.h"

class Model;
class World;
class SceneContext;

class WorldLoader {
  
public:
  
  void loadFromSceneFile(const std::string& filePath, World& world, SceneContext& sceneContext);
  void loadModel(Model* model, const std::string& modelFilePath);
  
private:
  
  void loadSceneItem(const json::Object& objectItem, World& world);
  Material loadMaterial(const json::Object& materialItem);
  void loadEffect(Material& material, const std::string& shaderFilePath);
  void loadTerrain(const json::Object& objectItem, World& world);
  
};

#endif
