#include "Model.h"

#include "Standard.h"
#include "ResourceCache.h"
#include "TextureCache.h"
#include "String.h"

#include "assimp.hpp"
#include "aiScene.h"
#include "aiPostProcess.h"

#include "MacPlatform.h"

#include "Mesh.h"

#include "Camera.h"
#include "Material.h"
#include "Shader.h"
#include "ShaderAttribs.h"

#include "Renderer.h"

#include <iostream>
#include "Matrix3x3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

Model* Model::model(const char* filepath) {
  Model* model = new Model();
  model->init();
  {
    Assimp::Importer importer;
    
    std::string fullPath = MacPlatform::instance()->path_for_file(filepath);
    const aiScene* scene = importer.ReadFile(fullPath.c_str(), aiProcess_PreTransformVertices);
    for (int i = 0; i < scene->mNumMeshes; i++) {
      aiMesh* aiMesh = scene->mMeshes[i];
      float* verts = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
      float* normals = new float[aiMesh->mNumVertices*sizeof(aiVector3D)];
      
      int vertIndex = 0;
      for (int vertexi = 0; vertexi < aiMesh->mNumVertices; vertexi++) {
        
        // vertex
        aiVector3D vertex = aiMesh->mVertices[vertexi];
        Vector4 originalVertex(vertex.x, vertex.y, vertex.z);
        Vector4 rotatedVertex = originalVertex;
        
        // normal
        aiVector3D normal = aiMesh->mNormals[vertexi];
        Vector4 originalNormal(normal.x, normal.y, normal.z);
        Vector4 rotatedNormal = originalNormal;
        
        verts[vertIndex] = rotatedVertex.x;
        normals[vertIndex] = rotatedNormal.x;
        vertIndex++;
        
        verts[vertIndex] = rotatedVertex.y;
        normals[vertIndex] = rotatedNormal.y;
        vertIndex++;
        
        verts[vertIndex] = rotatedVertex.z;
        normals[vertIndex] = rotatedNormal.z;
        vertIndex++;
      }
      
      Shader* shader = Shader::shader("vmvpcs.vsh", "fcls.fsh");
      Material* material = Material::material(shader);
      
      Mesh* mesh = Mesh::mesh(verts, normals, vertIndex + 1, material);
      model->addChild(mesh);

      aiMaterial* materialRaw = scene->mMaterials[aiMesh->mMaterialIndex];
      
      int textureCount = materialRaw->GetTextureCount(aiTextureType_DIFFUSE);
      for (int texturei = 0; texturei < textureCount; texturei++) {
        aiString texturePathRaw;
        materialRaw->GetTexture(aiTextureType_DIFFUSE, texturei, &texturePathRaw);
        
        String texturePathFull(texturePathRaw.data);
        String texturePath = texturePathFull.lastPathComponent();
        
        Texture* texture = TextureCache::instance()->addTexture(texturePath.c_str());
        material->setTexture(texture);
      }
      
      aiColor3D ambient;
      materialRaw->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
      material->setAmbient(ambient.r, ambient.g, ambient.b);
      
      aiColor3D diffuse;
      materialRaw->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
      material->setDiffuse(diffuse.r, diffuse.g, diffuse.b);
      
      aiColor3D specular;
      materialRaw->Get(AI_MATKEY_COLOR_SPECULAR, specular);
      material->setSpecular(specular.r, specular.g, specular.b);
    }
  }
  return model;
}
