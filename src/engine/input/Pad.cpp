#include "Pad.h"

#include "platform/PlatformDefs.h"
#include "memory/ScopeStack.h"

#include "IPad.h"

#ifdef PLATFORM_PS3
  #include "PS3Pad.h"
#endif

#include "NullPad.h"

IPad* Pad::pad_ = 0;

void Pad::init(ScopeStack* scopeStack) {
#ifdef PLATFORM_PS3
  pad_ = new PS3Pad();
#else
  pad_ = scopeStack->create<NullPad>();
#endif
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
