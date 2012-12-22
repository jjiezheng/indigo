#ifndef PS3PAD_H
#define PS3PAD_H

#include "IPad.h"

class PS3Pad : public IPad {

public:

	PS3Pad() 
		: leftStickY_(0.0f)
		, leftStickX_(0.0f)
		, rightStickX_(0.0f)
		, rightStickY_(0.0f)
		, leftShoulder_(false)
		, rightShoulder_(false) { };


public:

  void setup();

  void update();

public:

  float leftStickY();

  float leftStickX();

  float rightStickX();

  float rightStickY();

  bool leftShoulder();

  bool rightShoulder();

private:

  float leftStickY_;
  float leftStickX_;
  float rightStickX_;
  float rightStickY_;

private:

  bool leftShoulder_;
  bool rightShoulder_;

};

#endif