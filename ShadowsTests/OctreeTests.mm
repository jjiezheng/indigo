#import "OctreeTests.h"

#include "Octree.h"
#include "SceneNode.h"

#include "Frustum.h"

@implementation OctreeTests

- (void)testBoundsOfFrustum {
  Octree octree(2);
  SceneNode* node = SceneNode::node();
  node->setPosition(0, 0, -10);
//  octree.addNode(node);
  
  Frustum frustum(1.0f, -1.0f, 1.0f, -200.0f, -1.0f, 1.0f);
  bool result = octree.test(frustum);
  STAssertTrue(result, @"node should be within frustum");
}

@end