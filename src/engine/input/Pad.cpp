#include "Pad.h"

#include "platform/PlatformDefs.h"

#include "IPad.h"

#ifdef PLATFORM_PS3
  #include "PS3Pad.h"
#endif

#include "NullPad.h"

IPad* Pad::pad_ = 0;

void Pad::init() {
#ifdef PLATFORM_PS3
  pad_ = new PS3Pad();
#else
  pad_ = new NullPad();
#endif
<<<<<<< HEAD
  
=======
>>>>>>> 781288e0c35f52975ce30d42b07b4a37f0042aa1
  pad_->setup();
}

void Pad::update() {
  pad_->update();
}

float Pad::leftStickY() {
  return pad_->leftStickY();
}

float Pad::leftStickX() {
  return pad_->leftStickX();
}

float Pad::rightStickX() {
  return pad_->rightStickX();
}

float Pad::rightStickY() {
  return pad_->rightStickY();
}

bool Pad::leftShoulder() {
  return pad_->leftShoulder();
}

bool Pad::rightShoulder() {
  return pad_->rightShoulder();
}
