#ifndef IACTOR_H
#define IACTOR_H

class IActor {

public:

	virtual ~IActor() { };

public:

	virtual void init() = 0;

	virtual void update(float dt) = 0;

};

#endif