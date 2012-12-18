#include "WorldLoader.h"

#include <iostream>
#include <fstream>

#include "json/reader.h"
#include "io/Path.h"
#include "io/Log.h"

#include "core/String.h"
#include "maths/Angles.h"

#include "platform/PlatformDefs.h"
#include "serialization/BinaryModelDeserializer.h"

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


#include "GraphicsInterface.h"
#include "EffectCache.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "HeightMap.h"
#include "Light.h"
#include "SkyDome.h"
#include "Texture.h"
#include "World.h"
#include "SceneContext.h"

void WorldLoader::loadFromSceneFile(const std::string& filePath, World& world, SceneContext& sceneContext) {
  std::string fullFilePath = Path::pathForFile(filePath);
  std::ifstream levelFile(fullFilePath.c_str(), std::ifstream::in);
  
  if (!levelFile.is_open()) {
    LOG(LOG_CHANNEL_WORLDLOADER, "Unabled to load scene file %s", filePath.c_str());
    return;
  }

  json::Object sceneObject;
  json::Reader::Read(sceneObject, levelFile);

  if (sceneObject.Find("skydome") != sceneObject.end()) {
    json::String skydomeString = sceneObject["skydome"];
    std::string skydomePath = skydomeString.Value();

    SkyDome skydome;
    skydome.load(skydomePath);
    world.setSkyDome(skydome);
  }

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
    //loadTerrain((*tit), world);
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

        Vector3 direction(x, y, z);

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

          CSize shadowMapSize = GraphicsInterface::backBufferSize() * 1;
          light->setShadowMapResolution(shadowMapSize);

          unsigned int shadowMapDepthTexture = GraphicsInterface::createDepthTexture(shadowMapSize);
          light->setShadowMapDepthTexture(shadowMapDepthTexture);
          
          unsigned int shadowMapTexture = GraphicsInterface::createTexture(shadowMapSize, IGraphicsInterface::R8G8B8A8, 1, 1);
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
  json::String modelFilePath = objectItem["model"];

  levelpool::string fullFilePath = Path::pathForFile(modelFilePath).c_str();
//  Model* model = BinaryModelDeserializer(worldStack_).deserialize(fullFilePath);
//
//  json::Object positionObject = objectItem["position"];
//  
//  json::Number xNumber = positionObject["x"];
//  float x = xNumber.Value();
//  
//  json::Number yNumber = positionObject["y"];
//  float y = yNumber.Value();
//  
//  json::Number zNumber = positionObject["z"];
//  float z = zNumber.Value();
//  
//  Vector3 position(x, y, z);
//  Matrix4x4 localToWorld = Matrix4x4::translation(position);
//  model->setLocalToWorld(localToWorld);
//
//  world.addObject(model);
}

void WorldLoader::loadModel(Model* model, const std::string& modelFilePath) {
  std::string fullFilePath = Path::pathForFile(modelFilePath);
  //Model* model = BinaryModelDeserializer::deserialize(fullFilePath);

  std::string fullAssetFilePath = Path::pathForFile(fullFilePath);
  LOG(LOG_CHANNEL_WORLDLOADER, "Loading model %s", fullAssetFilePath.c_str());

  std::ifstream modelFile(fullFilePath.c_str(), std::ifstream::in);
  json::Object modelJSONObject;
  json::Reader::Read(modelJSONObject, modelFile);
  
  {  
    json::Array submeshesJSONArray = modelJSONObject["submeshes"];
    json::Array::iterator smit = submeshesJSONArray.begin();

    for (; smit != submeshesJSONArray.end(); ++smit) {
      json::Object submeshJSONObject = (*smit);
      json::Array verticesJSONArray = submeshJSONObject["vertices"];
      json::Array normalsJSONArray = submeshJSONObject["normals"];
      json::Array uvsJSONArray = submeshJSONObject["uvs"];

      unsigned int vertexCount = (unsigned int)(verticesJSONArray.Size() / 3.0f);
      
      unsigned int defi = 0;
      VertexDef* defs = new VertexDef[vertexCount];

      unsigned int uvIndex = 0;

      for (unsigned int index = 0; index < verticesJSONArray.Size();) {

        VertexDef def;

        json::Number vertexXJSONNumber = verticesJSONArray[index];
        float vertexX = vertexXJSONNumber.Value();
        def.vertex.x = vertexX; 

        json::Number normalXJSONNumber = normalsJSONArray[index];
        float normalX = normalXJSONNumber.Value();
        def.normal.x = normalX;

        json::Number uvUJSONNumber = uvsJSONArray[uvIndex];
        float uvU = uvUJSONNumber.Value();
        def.uv.x = uvU;

        uvIndex++;
        index++;


        json::Number vertexYJSONNumber = verticesJSONArray[index];
        float vertexY = vertexYJSONNumber.Value();
        def.vertex.y = vertexY; 

        json::Number normalYJSONNumber = normalsJSONArray[index];
        float normalY = normalYJSONNumber.Value();
        def.normal.y = normalY;

        json::Number uvVJSONNumber = uvsJSONArray[uvIndex];
        float uvV = uvVJSONNumber.Value();
        def.uv.y = uvV;

        uvIndex++;
        index++;


        json::Number vertexZJSONNumber = verticesJSONArray[index];
        float vertexZ = vertexZJSONNumber.Value();
        def.vertex.z = vertexZ;


        json::Number normalZJSONNumber = normalsJSONArray[index];
        float normalZ = normalZJSONNumber.Value();
        def.normal.z = normalZ;

        index++;

        defs[defi++] = def;
      }

      json::Object materialJSONObject = submeshJSONObject["material"];
      Material material = loadMaterial(materialJSONObject);

      Mesh mesh;
      mesh.init(defs, vertexCount, TRIANGLE_LIST);
      mesh.setMaterial(material);
      model->addMesh(mesh);
    }
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
//  std::string fullEffectPath = Path::pathForFile(shaderFilePath);
//  IEffect* effect = EffectCache::instance()->loadEffect(fullEffectPath);
//  material.setEffect(effect);
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
