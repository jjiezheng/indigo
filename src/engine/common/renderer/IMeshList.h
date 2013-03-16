#ifndef IMESH_LIST_H
#define IMESH_LIST_H

class Mesh;

class IMeshList {

public:

  virtual ~IMeshList() { };

public:

  virtual void collectMesh(const Mesh* const mesh) = 0;

  virtual std::vector<const Mesh*>::const_iterator begin() = 0;

  virtual std::vector<const Mesh*>::const_iterator end() = 0;

};

#endif