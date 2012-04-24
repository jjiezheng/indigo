#include "Octree.h"

Octree::Octree(int depth) {
  for (int i = 0; i < 8; i++) {
    Octree* octree = new Octree(depth - 1);
    nodes_.push_back(octree);
  }
}

void Octree::addNode(Octree* node) {
  
}

bool Octree::test(const Frustum &frustum) {
  
  return false;
}