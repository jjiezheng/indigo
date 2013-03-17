#ifndef IEDITOR_OVERLAY_H
#define IEDITOR_OVERLAY_H

class IViewer;
class World;

class IEditorOverlay {

public:

  virtual ~IEditorOverlay() { };

public:

  virtual void init() = 0;

  virtual void render(IViewer* viewer, const World& world) const = 0;

};

#endif