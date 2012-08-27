#include "WorldLoader.h"

#include <iostream>
#include <fstream>

#include "json/reader.h"
#include "io/Path.h"
#include "io/Log.h"

#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>

#include "Mesh.h"
#include "maths/Vector4.h"
#include "VertexDefinition.h"
#include "Model.h"
#include "Material.h"
#include "IEffect.h"

#include "MaterialParameter.h"
#include "Vector3MaterialParameter.h"
#include "IntegerMaterialParameter.h"
#include "FloatMaterialParameter.h"

#include "World.h"
#include "SceneContext.h"

#include "Light.h"
#include "SkyDome.h"
#include "Texture.h"

#include "GraphicsInterface.h"
#include "EffectCache.h"
#include "core/String.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "maths/Angles.h"

#include "HeightMap.h"

void WorldLoader::loadFromSceneFile(const std::string& filePath, World& world, SceneContext& sceneContext) {
  std::string fullFilePath = Path::pathForFile(filePath);
  std::ifstream levelFile(fullFilePath.c_str(), std::ifstream::in);
  json::Object sceneObject;
  json::Reader::Read(sceneObject, levelFile);

  json::String skydomeString = sceneObject["skydome"];
  std::string skydomePath = skydomeString.Value();

  SkyDome skydome;
  skydome.load(skydomePath);
  world.setSkyDome(skydome);

  json::Object backgroundColor = sceneObject["backgroundColor"];
  json::Number redNumber = backgroundColor["r"];
  float r = redNumber.Value();

  json::Number greenNumber = backgroundColor["g"];
  float g = greenNumber.Value();

  json::Number blueNumber = backgroundColor["b"];
  float b = blueNumber.Value();

  Color4 backgroundColor3(r, g, b, 1);
  sceneContext.setBackgroundColor(backgroundColor3);

  json::Array terrainArray = sceneObject["terrain"];
  json::Array::iterator tit = terrainArray.begin();

  for(; tit != terrainArray.end(); ++tit) {
    loadTerrain((*tit), world);
  }
  
  json::Array objectsArray = sceneObject["objects"];
  json::Array::iterator oit = objectsArray.begin();
  
  for (; oit != objectsArray.end(); ++oit) {
    loadSceneItem((*oit), world);
  }
  
  json::Array lightsArray = sceneObject["lights"];
  json::Array::iterator lit = lightsArray.begin();

  for (; lit != lightsArray.end(); ++lit) {
    json::String lightTypeString = (*lit)["type"];
    String lightType = lightTypeString.Value();

    if (lightType == "directional") {

      DirectionalLight light;
      
      {
        json::Object directionObject = (*lit)["direction"];

        json::Number xNumber = directionObject["x"];
        float x = xNumber.Value();

        json::Number yNumber = directionObject["y"];
        float y = yNumber.Value();

        json::Number zNumber = directionObject["z"];
        float z = zNumber.Value();

        Vector4 direction(x, y, z, 1.0f);

        light.setDirection(direction);
      }

      {
        json::Object colorObject = (*lit)["color"];
        
        json::Number rNumber = colorObject["r"];
        float r = rNumber.Value();
        
        json::Number gNumber = colorObject["g"];
        float g = gNumber.Value();

        json::Number bNumber = colorObject["b"];
        float b = bNumber.Value();      
        
        light.setColor(Color3(r, g, b));
      }
      
      sceneContext.addDirectionalLight(light);    
    }

    if (lightType == "point") {

      PointLight light;

      {
        json::Number radius = (*lit)["radius"];
        light.setRadius(radius);
      }
      
      {
        json::Object positionObject = (*lit)["position"];

        json::Number xNumber = positionObject["x"];
        float x = xNumber.Value();

        json::Number yNumber = positionObject["y"];
        float y = yNumber.Value();

        json::Number zNumber = positionObject["z"];
        float z = zNumber.Value();

        Vector4 position(x, y, z, 0.0f);

        light.setPosition(position);
      }

      {
        json::Object colorObject = (*lit)["color"];

        json::Number rNumber = colorObject["r"];
        float r = rNumber.Value();

        json::Number gNumber = colorObject["g"];
        float g = gNumber.Value();

        json::Number bNumber = colorObject["b"];
        float b = bNumber.Value();      

        light.setColor(Color3(r, g, b));
      }

      sceneContext.addPointLight(light); 
    }

    if (lightType == "spot") {

      SpotLight* light = new SpotLight();

      {
        json::Number outerAngle = (*lit)["outerangle"];
        light->setOuterAngle(toRadians(outerAngle));
      }

      {
        json::Number innerAngle = (*lit)["innerangle"];
        light->setInnerAngle(toRadians(innerAngle));
      }

      {
        json::Number decay = (*lit)["decay"];
        light->setDecay(decay);
      }

      {
        json::Number length = (*lit)["length"];
        light->setLength(length);
      }
      
      {
        json::Object positionObject = (*lit)["position"];

        json::Number xNumber = positionObject["x"];
        float x = xNumber.Value();

        json::Number yNumber = positionObject["y"];
        float y = yNumber.Value();

        json::Number zNumber = positionObject["z"];
        float z = zNumber.Value();

        Vector4 position(x, y, z, 0.0f);

        light->setPosition(position);
      }

      {
        json::Object positionObject = (*lit)["orientation"];

        json::Number xNumber = positionObject["x"];
        float x = xNumber.Value();

        json::Number yNumber = positionObject["y"];
        float y = yNumber.Value();

        json::Number zNumber = positionObject["z"];
        float z = zNumber.Value();

        Matrix4x4 orientation = Matrix4x4::rotationZ(toRadians(z)) * Matrix4x4::rotationY(toRadians(y)) * Matrix4x4::rotationX(toRadians(x));

        light->setOrientation(orientation);
      }

      {
        json::Object directionObject = (*lit)["direction"];

        json::Number xNumber = directionObject["x"];
        float x = xNumber.Value();

        json::Number yNumber = directionObject["y"];
        float y = yNumber.Value();

        json::Number zNumber = directionObject["z"];
        float z = zNumber.Value();

        Vector4 direction(x, y, z, 1.0f);

        light->setDirection(direction);
      }

      {
        json::Object colorObject = (*lit)["color"];

        json::Number rNumber = colorObject["r"];
        float r = rNumber.Value();

        json::Number gNumber = colorObject["g"];
        float g = gNumber.Value();

        json::Number bNumber = colorObject["b"];
        float b = bNumber.Value();      

        light->setColor(Color3(r, g, b));
      }

      {
        json::Boolean castsShadowsBoolean = (*lit)["castsshadows"];
        bool castsShadows = castsShadowsBoolean.Value();

        if (castsShadows) {
          light->setCastsShadows(castsShadows);
          
          unsigned int shadowMapTexture = GraphicsInterface::createTexture(GraphicsInterface::screenSize(), 1, 1);
          light->setShadowMapTexture(shadowMapTexture);

          unsigned int shadowMapRendeTarget = GraphicsInterface::createRenderTarget(shadowMapTexture);
          light->setShadowMapRenderTarget(shadowMapRendeTarget);
        }
      }

      sceneContext.addSpotLight(light); 
    }
  }
}

void WorldLoader::loadSceneItem(const json::Object& objectItem, World& world) {
  Model* model = new Model();

  json::String modelFilePath = objectItem["model"];
  
  json::Object positionObject = objectItem["position"];
  
  json::Number xNumber = positionObject["x"];
  float x = xNumber.Value();
  
  json::Number yNumber = positionObject["y"];
  float y = yNumber.Value();
  
  json::Number zNumber = positionObject["z"];
  float z = zNumber.Value();
  
  Vector3 position(x, y, z);
  Matrix4x4 localToWorld = Matrix4x4::translation(position);
  model->setLocalToWorld(localToWorld);
  
  loadModel(model, modelFilePath);

  //loadMaterial(model, materialFilePath);
  world.addObject(model);
}

void WorldLoader::loadModel(Model* model, const std::string& modelFilePath) {
  std::string fullFilePath = Path::pathForFile(modelFilePath);
  std::ifstream modelFile(fullFilePath.c_str(), std::ifstream::in);
  json::Object modelObject;
  json::Reader::Read(modelObject, modelFile);

  std::vector<Material> materials;

   {
    json::Array materialsArray = modelObject["materials"];
    json::Array::const_iterator mit = materialsArray.begin();
    for (; mit != materialsArray.end(); ++mit) {
      Material material = loadMaterial((*mit));
      materials.push_back(material);
    }
  }

  json::String assetFilePath = modelObject["mesh"];
  
  {  
    std::string fullAssetFilePath = Path::pathForFile(assetFilePath);
    LOG(LOG_CHANNEL_WORLDLOADER, "Loading model %s", fullAssetFilePath.c_str());

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(fullAssetFilePath.c_str(), aiProcess_PreTransformVertices  );
    LOG(LOG_CHANNEL_WORLDLOADER, "Submesh count: %d", scene->mNumMeshes);
    
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
      aiMesh* aiMesh = scene->mMeshes[i];
      VertexDef* defs = new VertexDef[aiMesh->mNumVertices];

      for (unsigned int vertexi = 0; vertexi < aiMesh->mNumVertices; vertexi++) {
        VertexDef def;

        aiVector3D vertex = aiMesh->mVertices[vertexi];
        def.vertex.x = vertex.x; 
        def.vertex.y = vertex.y; 
        def.vertex.z = vertex.z; 
        //LOG(LOG_CHANNEL_WORLDLOADER, "vert: %s", def.vertex.toString().c_str());

        aiVector3D normal = aiMesh->mNormals[vertexi];
        def.normal.x = normal.x; 
        def.normal.y = normal.y; 
        def.normal.z = normal.z; 
        //LOG(LOG_CHANNEL_WORLDLOADER, "norm: %s", def.normal.toString().c_str());

        if (aiMesh->mTextureCoords[0]) {
          aiVector3D uv = aiMesh->mTextureCoords[0][vertexi];
          def.uv.x = uv.x; 
          def.uv.y = uv.y; 
        }
        //LOG(LOG_CHANNEL_WORLDLOADER, "uv: %s", def.uv.toString().c_str());
        defs[vertexi] = def;
      }

      Mesh mesh;
      Material material = materials[i];
      mesh.init(defs, aiMesh->mNumVertices, TRIANGLE_LIST);
      mesh.setMaterial(material);
      model->addMesh(mesh);
      
    }
    
    importer.FreeScene();
  }
}

Material WorldLoader::loadMaterial(const json::Object& materialObject) {
 
  json::String effectFilePath = materialObject["effect"];
 
  Material material;
  loadEffect(material, effectFilePath.Value()); 
  
  json::Object parameters = materialObject["parameters"];
  json::Object::const_iterator pit = parameters.begin();
  for (; pit != parameters.end(); ++pit) {
    json::String parameterNameString = (*pit).name;
    std::string parameterName = parameterNameString.Value();
    
    json::String parameterTypeString = (*pit).element["type"];
    std::string parameterType = parameterTypeString.Value();
        
    if (parameterType.compare("color3") == 0) {
      json::Number redNumber = (*pit).element["r"];
      float r = redNumber.Value();

      json::Number greenNumber = (*pit).element["g"];
      float g = greenNumber.Value();

      json::Number blueNumber = (*pit).element["b"];
      float b = blueNumber.Value();
      
      Vector3 color3(r, g, b);
      Vector3MaterialParameter* parameter = new Vector3MaterialParameter(parameterName, color3);
      material.setParameter(parameter);
    }
    
    if (parameterType.compare("int") == 0) {
      json::Number valueNumber = (*pit).element["value"];
      int value = (int)valueNumber.Value();
      IntegerMaterialParameter* parameter = new IntegerMaterialParameter(parameterName, value);
      material.setParameter(parameter);
    }
    
    if (parameterType.compare("float") == 0) {
      json::Number valueNumber = (*pit).element["value"];
      float value = valueNumber.Value();
      FloatMaterialParameter* parameter = new FloatMaterialParameter(parameterName, value);
      material.setParameter(parameter);
    }
  }

  json::Object textures = materialObject["textures"];
  json::Object::const_iterator tit = textures.begin();
  for (; tit != textures.end(); ++tit) {
    json::String textureTypeString = (*tit).name;
    std::string textureType = textureTypeString.Value();
    
    json::String textureFileString = (*tit).element;
    std::string textureFile = textureFileString.Value();

    Texture texture;
    texture.init(textureFile.c_str());
    material.addTexture(textureType, texture);
  }

  return material;
}

void WorldLoader::loadEffect(Material& material, const std::string &shaderFilePath) { 
  std::string fullEffectPath = Path::pathForFile(shaderFilePath);
  int effectId = EffectCache::instance()->loadEffect(fullEffectPath);
  material.setEffect(effectId);
}

void WorldLoader::loadTerrain(const json::Object& objectItem, World& world) {
  json::String terrainFileString = objectItem["terrain"];
  std::string terrainFilePath = terrainFileString.Value();
  std::string fullTerrainFilePath = Path::pathForFile(terrainFilePath);
  std::ifstream terrainFile(fullTerrainFilePath.c_str(), std::ifstream::in);
  
  json::Object terrainObject;
  json::Reader::Read(terrainObject, terrainFile);

  json::String heightmapString = terrainObject["heightmap"];
  std::string heightmap = heightmapString.Value();

  HeightMap heightMap;
  heightMap.load(heightmap);

  json::Object materialObject = terrainObject["material"];
  Material material = loadMaterial(materialObject);

  Mesh mesh;
  mesh.init(heightMap.vertices, heightMap.vertexCount, heightMap.vertexFormat);
  mesh.setMaterial(material);

  Model* model = new Model();
  model->addMesh(mesh);

  world.addObject(model);
}
