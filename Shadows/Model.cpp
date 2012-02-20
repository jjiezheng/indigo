#include "Model.h"

#include "Standard.h"
#include "ResourceCache.h"

#include "assimp.hpp"
#include "aiScene.h"
#include "aiPostProcess.h"

#include "MacPlatform.h"

#include "Mesh.h"

#include "Camera.h"
#include "Shader.h"
#include "ShaderAttribs.h"

#include "Renderer.h"

#include <iostream>

Model* Model::model(const char* filepath) {
  Model* model = new Model();
  model->init();
  model->load(filepath);
  return model;
}

void Model::init() {
  rotationX_ = 0;
  rotationZ_ = 0;
}

void Model::load(const char *filepath) {
  Assimp::Importer importer;
  
  std::string fullPath = MacPlatform::instance()->path_for_file(filepath);
  const aiScene* scene = importer.ReadFile(fullPath.c_str(), aiProcess_PreTransformVertices);
  for (int i = 0; i < scene->mNumMeshes; i++) {
    aiMesh* aiMesh = scene->mMeshes[i];
    float* verts = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
    float* normals = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
        
    int vertIndex = 0;
    for (int vertexi = 0; vertexi < aiMesh->mNumVertices; vertexi++) {
      aiVector3D vertex = aiMesh->mVertices[vertexi];
      aiVector3D normal = aiMesh->mNormals[vertexi];
      
      verts[vertIndex] = vertex.x;
      normals[vertIndex] = normal.x;
      vertIndex++;
      
      verts[vertIndex] = vertex.z;
      normals[vertIndex] = normal.z;
      vertIndex++;
      
      verts[vertIndex] = -vertex.y;
      normals[vertIndex] = -normal.y;
      vertIndex++;
    }
    
    Mesh* mesh = Mesh::mesh(verts, normals, vertIndex + 1);
    
    aiMaterial* material = scene->mMaterials[aiMesh->mMaterialIndex];

    aiColor3D ambient;
    material->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
    mesh->setAmbient(ambient.r, ambient.g, ambient.b);
    
    aiColor3D diffuse;
    material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
    mesh->setDiffuse(diffuse.r, diffuse.g, diffuse.b);
    
    aiColor3D specular;
    material->Get(AI_MATKEY_COLOR_SPECULAR, specular);
    mesh->setSpecular(specular.r, specular.g, specular.b);
    
    meshes_.push_back(mesh);
  }
}

void Model::render(Renderer* renderer) {
  renderer->queueModel(this);
}

void Model::render(Shader* shader) const {
  glm::mat4 rotation(1.0f);
  rotation = glm::rotate(rotation, rotationZ_, glm::vec3(0.0f, 0.0f, 1.0f));
  rotation = glm::rotate(rotation, rotationY_, glm::vec3(0.0f, 1.0f, 0.0f));
  rotation = glm::rotate(rotation, rotationX_, glm::vec3(1.0f, 0.0f, 0.0f));
  
  glm::mat3 normalMatrix(rotation);
  shader->set_uniform(normalMatrix, "normalMatrix");
  
  glm::mat4 translation(1.0f);
  translation = glm::translate(translation, position_);
  
  glm::mat4 model = translation * rotation;
  shader->set_uniform(model, "model");
      
  for (Mesh* mesh : meshes_) {
    mesh->render(shader);
  }
}
