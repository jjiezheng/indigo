#ifndef EFFECT_MESH_LIST_H
#define EFFECT_MESH_LIST_H
#include "core/HashMap.h"

#include "IMeshList.h"

class IEffect;

class EffectMeshList : public IMeshList {

public:

  void collectMesh(const Mesh* const mesh);

public:

  hash_map<IEffect*, std::vector<const Mesh*> >::const_iterator begin();

  hash_map<IEffect*, std::vector<const Mesh*> >::const_iterator end();

private:

  hash_map<IEffect*, std::vector<const Mesh*> > meshes_;

};

inline void EffectMeshList::collectMesh(const Mesh* const mesh) {
  Material material = mesh->material();
  IEffect* effect = material.effect();
  meshes_[effect].push_back(mesh);
}

inline hash_map<IEffect*, std::vector<const Mesh*> >::const_iterator EffectMeshList::begin() {
  return meshes_.begin();
}

inline hash_map<IEffect*, std::vector<const Mesh*> >::const_iterator EffectMeshList::end() {
  return meshes_.end();
}

#endif