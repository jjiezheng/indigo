#ifndef IEDITOR_TOOL_H
#define IEDITOR_TOOL_H

class IViewer;
class Selection;
class Ray;

class IEditorTool {

public:

  virtual ~IEditorTool() { };

public:

  IEditorTool()
    : isActive_(false) { }

public:

  virtual void init() = 0;

  virtual void render(IViewer* viewer) const = 0;

  virtual void update(float dt, const Selection& selection, const Ray& mouseRay, const IViewer* viewer) = 0;

public:

  virtual bool mousePick(const Ray& ray) = 0;

  virtual void mouseUp() = 0;

public:

  void setActive(bool isActive);

  bool isActive() const;

protected:

  bool isActive_;

};

inline void IEditorTool::setActive(bool isActive) {
  isActive_ = isActive;
}

inline bool IEditorTool::isActive() const {
  return isActive_;
}

#endif