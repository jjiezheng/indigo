#ifndef FLAT_MESH_LIST_H
#define FLAT_MESH_LIST_H

#include "IMeshList.h"
#include <vector>

class FlatMeshList : public IMeshList {

public:

  void collectMesh(const Mesh* const mesh);

public:

  std::vector<const Mesh*>::const_iterator begin();

  std::vector<const Mesh*>::const_iterator end();

private:

  std::vector<const Mesh*> meshes_;

};

inline void FlatMeshList::collectMesh(const Mesh* const mesh) {
  meshes_.push_back(mesh);
}

inline std::vector<const Mesh*>::const_iterator FlatMeshList::begin() {
  return meshes_.begin();
}

inline std::vector<const Mesh*>::const_iterator FlatMeshList::end() {
  return meshes_.end();
}

#endif