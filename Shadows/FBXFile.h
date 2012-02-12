#ifndef CubeFX_FBXFile_h
#define CubeFX_FBXFile_h

#include <string>
#include <deque>

#include <fbxsdk.h>
#include "FBXMesh.h"

class FBXFile {
  
  typedef std::deque<FBXMesh> MeshDeque;
  
public:
  
  FBXFile(const std::string& path) 
  : path(path) { };
  
  void load();
  
  MeshDeque meshes() const;
  
  
private:
  
  std::string path;
  
  KFbxNode* root_node;
  
  void recurse_over_model(const MeshDeque& complete_meshes, KFbxNode* fbx_node) const;
  
};


#endif
