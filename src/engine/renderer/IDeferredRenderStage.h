#ifndef IDEFERRED_RENDER_STAGE_H
#define IDEFERRED_RENDER_STAGE_H

#include <vector>

class IViewer;
class World;
class SceneContext;
class CSize;

class IDeferredRenderStage {

public:

  virtual ~IDeferredRenderStage() { };

public:

  virtual void init(const CSize &screenSize) = 0;

};

#endif