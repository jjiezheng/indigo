#ifndef CONTROL_H
#define CONTROL_H

class Matrix4x4;

class Control {

public:

	virtual ~Control() { };

public:

	Control()
		: isVisible_(true)
		, tag_(0) { }

public:

	virtual void render(const Matrix4x4& projection) = 0;

	virtual void update(float dt) = 0;

public:

	void setTag(unsigned int tag);

	unsigned int tag() const;

public:

	void setVisible(bool isVisible);
  
  bool isVisible() const;
  
  void toggleVisible();

protected:

	bool isVisible_;
	unsigned int tag_;

};

inline void Control::setTag(unsigned int tag) {
	tag_ = tag;
}

inline unsigned int Control::tag() const {
	return tag_;
}

inline void Control::setVisible(bool isVisible) {
	isVisible_ = isVisible;
}

inline bool Control::isVisible() const {
  return isVisible_;
}

inline void Control::toggleVisible() {
  isVisible_ = !isVisible_;
}

#endif
