#include "WorldLoader.h"

#include "json/reader.h"
#include "MacPlatform.h"

#include <iostream>
#include <fstream>

#include "assimp.hpp"
#include "aiScene.h"
#include "aiPostProcess.h"

#include "Mesh.h"
#include "Vector4.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"

#include "ShaderResource.h"
#include "ResourceCache.h"

#include "MaterialParameter.h"
#include "Vector3MaterialParameter.h"
#include "IntegerMaterialParameter.h"

#include "World.h"
#include "SceneContext.h"

#include "Light.h"
#include "SkyBox.h"

void WorldLoader::loadFromSceneFile(const std::string& filePath, World& world, SceneContext& sceneContext) {
  std::string fullFilePath = MacPlatform::instance()->path_for_file(filePath);
  std::ifstream levelFile(fullFilePath, std::ifstream::in);
  json::Object sceneObject;
  json::Reader::Read(sceneObject, levelFile);
  
  json::String skyboxString = sceneObject["skybox"];
  std::string skyboxBasename = skyboxString.Value();
  
  SkyBox skybox;
  skybox.load(skyboxBasename);
  world.setSkyBox(skybox);
  
  json::Array objectsArray = sceneObject["objects"];
  
  for (json::Object& objectItem : objectsArray)  {
    loadSceneItem(objectItem, world);
  }
  
  json::Array lightsArray = sceneObject["lights"];
  
  for (json::Object& lightItem : lightsArray)  {
    Light light;
    
    {
      json::Object positionObject = lightItem["position"];
      
      json::Number xNumber = positionObject["x"];
      float x = xNumber.Value();
      
      json::Number yNumber = positionObject["y"];
      float y = yNumber.Value();
      
      json::Number zNumber = positionObject["z"];
      float z = zNumber.Value();
      
      Vector4 position(x, y, z);
    
      light.setPosition(position);
    }
    
    sceneContext.addLight(light);
    
//    {
//      json::Object positionObject = lightItem["orientation"];
//      
////      json::Number xNumber = positionObject["x"];
////      float x = xNumber.Value();
//      
//      json::Number yNumber = positionObject["y"];
//      float y = yNumber.Value();
//      Matrix4x4 rotationY = Matrix4x4::rotationY(y);
//      
////      json::Number zNumber = positionObject["z"];
////      float z = zNumber.Value();
//      
//
//      light.setPosition(position);
//    }
  }
}

void WorldLoader::loadSceneItem(const json::Object& objectItem, World& world) {
  Model* model = new Model();

  json::String meshFilePath = objectItem["mesh"];
  json::String materialFilePath = objectItem["material"];
  
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
  
  loadModel(model, meshFilePath);
  loadMaterial(model, materialFilePath);
  world.addObject(model);
}

void WorldLoader::loadModel(Model* model, const std::string& modelFilePath) {
  Assimp::Importer importer;
  
  std::string fullPath = MacPlatform::instance()->path_for_file(modelFilePath);
  const aiScene* scene = importer.ReadFile(fullPath.c_str(), aiProcess_PreTransformVertices);
  
  for (int i = 0; i < scene->mNumMeshes; i++) {
    aiMesh* aiMesh = scene->mMeshes[i];
    float* verts = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
    float* normals = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
    float* uvs = new float[aiMesh->mNumVertices*sizeof(aiVector2D)];
    
    int vertIndex = 0;
    int uvIndex = 0;
    for (int vertexi = 0; vertexi < aiMesh->mNumVertices; vertexi++) {
      
      // vertex
      aiVector3D vertex = aiMesh->mVertices[vertexi];
      Vector4 originalVertex(vertex.x, vertex.y, vertex.z);
      Vector4 rotatedVertex = originalVertex;
      
      // normal
      aiVector3D normal = aiMesh->mNormals[vertexi];
      Vector4 originalNormal(normal.x, normal.y, normal.z);
      Vector4 rotatedNormal = originalNormal;
      
      //        // uv
      //        aiVector3D uv = aiMesh->mTextureCoords[0][vertexi];
      //        Vector2 originalUV(uv.x, uv.y);
      //        Vector2 rotatedUV = originalUV;
      
      verts[vertIndex] = rotatedVertex.x;
      normals[vertIndex] = rotatedNormal.x;
      //        uvs[uvIndex] = rotatedUV.x;
      uvIndex++;
      vertIndex++;
      
      verts[vertIndex] = rotatedVertex.y;
      normals[vertIndex] = rotatedNormal.y;
      //        uvs[uvIndex] = rotatedUV.y;
      uvIndex++;
      vertIndex++;
      
      verts[vertIndex] = rotatedVertex.z;
      normals[vertIndex] = rotatedNormal.z;
      vertIndex++;
    }
    
    Mesh mesh(verts, normals, uvs, vertIndex + 1);
    mesh.init();
    model->addMesh(mesh);
  }
}

void WorldLoader::loadMaterial(Model* model, const std::string& materialFilePath) {
  std::string fullMaterialFilePath = MacPlatform::instance()->path_for_file(materialFilePath);
  
  std::ifstream materialFile(fullMaterialFilePath, std::ifstream::in);
  
  json::Object materialObject;
  json::Reader::Read(materialObject, materialFile); 

  json::String shaderFilePath = materialObject["shader"];
 
  Material material;
  loadShader(material, shaderFilePath.Value());
  
  json::Object parameters = materialObject["parameters"];
  
  for (json::Object::Member& member : parameters) {
    json::String parameterNameString = member.name;
    std::string parameterName = parameterNameString.Value();
    
    json::String parameterTypeString = member.element["type"];
    std::string parameterType = parameterTypeString.Value();
    
    if (parameterType.compare("color3") == 0) {
      json::Number redNumber = member.element["r"];
      float r = redNumber.Value();

      json::Number greenNumber = member.element["g"];
      float g = greenNumber.Value();

      json::Number blueNumber = member.element["b"];
      float b = blueNumber.Value();
      
      Vector3 color3(r, g, b);
      Vector3MaterialParameter* parameter = new Vector3MaterialParameter(parameterName, color3);
      material.setParameter(parameter);
    }
    
    if (parameterType.compare("int") == 0) {
      json::Number valueNumber = member.element["value"];
      int value = valueNumber.Value();
      IntegerMaterialParameter* parameter = new IntegerMaterialParameter(parameterName, value);
      material.setParameter(parameter);
    }
  }
  
  model->setMaterial(material);
}

void WorldLoader::loadShader(Material& material, const std::string &shaderFilePath) {
  
  Shader shader;
  std::string fullShaderFilePath = MacPlatform::instance()->path_for_file(shaderFilePath);
  std::ifstream shaderFile(fullShaderFilePath, std::ifstream::in);
  
  json::Object shaderObject;
  LOG(LOG_CHANNEL_WORLDLOADER, "loading shader %s", shaderFilePath.c_str());
  json::Reader::Read(shaderObject, shaderFile); 

  json::String vertexFilePath = shaderObject["vertex"];
  json::String fragmentFilePath = shaderObject["fragment"];
   
  ShaderResource* resource = ResourceCache::instance()->load_shader(vertexFilePath.Value(), fragmentFilePath.Value()); 
  
  shader.compile_vertex(resource->vertex_source());
  shader.compile_fragment(resource->fragment_source());
  
  json::Object attributesArray = shaderObject["attributes"];
  for (json::Object::Member& attributeMember : attributesArray) {
    json::Number attributeIndexNumber = attributeMember.element;
    int attributeIndex = attributeIndexNumber.Value();
    std::string attributeName = attributeMember.name;
    shader.bind_attribute(attributeIndex, attributeName.c_str());
  }
  
  shader.link();
  
  json::Array uniformsArray = shaderObject["uniforms"];
  
  for (json::String& uniformString : uniformsArray) {
    std::string uniform = uniformString.Value();
    shader.add_uniform(uniform.c_str());
  }
  
  material.setShader(shader);
}