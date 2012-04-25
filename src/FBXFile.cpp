#include "FBXFile.h"

#include "Standard.h"

void FBXFile::load() {
  KFbxSdkManager* manager = KFbxSdkManager::Create();
  
  KFbxIOSettings* ios = KFbxIOSettings::Create(manager, IOSROOT);
  manager->SetIOSettings(ios);
  
  KFbxImporter* importer = KFbxImporter::Create(manager, "");
  
  const char* filename = "/Users/nk/Desktop/untitled.fbx";
  if(!importer->Initialize(filename, -1, manager->GetIOSettings())) {
    LOG("failed to import %s", filename);
    LOG("%s", importer->GetLastErrorString());
    return;
  }
  
  KFbxScene* scene = KFbxScene::Create(manager, "scene");
  importer->Import(scene);
  importer->Destroy();
  
  
  root_node = scene->GetRootNode();
}

void FBXFile::recurse_over_model(const MeshDeque& complete_meshes, KFbxNode* fbx_node) const {
  KFbxGeometryConverter converter(fbx_node->GetFbxSdkManager());
  
  if (converter.TriangulateInPlace(fbx_node)) {
    KFbxMesh* mesh = fbx_node->GetMesh();
    
    if (mesh) {
      FBXMesh fbx_mesh;
      fbx_mesh.vertex_count = mesh->GetPolygonVertexCount();
      fbx_mesh.vertices = new float[fbx_mesh.vertex_count];
      int vertex_offset = 0;
      for (int poly_index = 0; poly_index < mesh->GetPolygonCount(); poly_index++) {
        for (int vertex_index = 0; vertex_index < 3; vertex_index++) {
          int vertex_position = mesh->GetPolygonVertex(poly_index, vertex_index);
          KFbxVector4 vertex = mesh->GetControlPoints()[vertex_position];
          fbx_mesh.vertices[vertex_offset] = vertex.GetAt(vertex_offset); vertex_offset++;
          fbx_mesh.vertices[vertex_offset] = vertex.GetAt(vertex_offset); vertex_offset++;
          fbx_mesh.vertices[vertex_offset] = vertex.GetAt(vertex_offset); vertex_offset++;
        }
      }
    }
    
  }
  
  for(int j = 0; j < fbx_node->GetChildCount(); j++) {
    recurse_over_model(complete_meshes, fbx_node->GetChild(j));
  }
}

FBXFile::MeshDeque FBXFile::meshes() const {
  MeshDeque meshes;
  this->recurse_over_model(meshes, root_node);
  return meshes;
}