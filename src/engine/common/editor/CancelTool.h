#ifndef CANCEL_TOOL_H
#define CANCEL_TOOL_H

#include "IEditorTool.h"

class CancelTool : public IEditorTool {

public:

  void init()  { };

  void render(IViewer* viewer) const { };

  void update(float dt, const Selection& selection) { };

  bool mousePick(const Ray& ray) { return false; };

};

#endif