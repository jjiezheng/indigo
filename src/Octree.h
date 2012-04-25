#ifndef OCTREE_H
#define OCTREE_H

#include <vector>

class SceneNode;
class Frustum;

class Octree {
  
public:
  
  Octree(int depth);
  
public:
  
  void addNode(Octree* node);
  
  void addSceneNode(SceneNode* node);
  
  bool test(const Frustum& frustum);

private:
  
  void fill(int depth);
  
private:
  
  std::vector<Octree*> nodes_;
  
};

#endif
