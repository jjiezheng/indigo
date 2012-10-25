#include "PS3Keyboard.h"

#include <cell/keyboard.h>

#include "io/Log.h"

#include <stdio.h>
#include <string.h>

#include "IKeyboardListener.h"

#define MAX_KEYBOARD 1

void PS3Keyboard::setup() {
  int32_t ret = cellKbInit(MAX_KEYBOARD);
  if (ret != CELL_OK) {
    LOG(LOG_CHANNEL_INPUT, "Failed to init pad");
  }
	memset(keyStates_, 0, sizeof(bool) * 256);
}

void PS3Keyboard::update() {
  static CellKbInfo keyboardInfo;
  int32_t ret;
  if ((ret = cellKbGetInfo(&keyboardInfo)) != CELL_OK) {
    return;
  }

  static CellKbData keyboardData;

  for (int i = 0; i < MAX_KEYBOARD; i++) {
    ret = cellKbRead(i, &keyboardData);

    if (0 != ret || keyboardData.len == 0) {
      continue;
    }

    memset(keyStates_, 0, sizeof(bool) * 256);

    for (unsigned int j = 0; j < keyboardData.len; j++) {
      int keyCode = keyboardData.keycode[j];
      bool keyDown = keyStates_[keyCode];
      keyStates_[keyCode] = true;
      if (!keyDown) {
        if (keyDownListener_ != NULL) {
          keyDownListener_->keyUp(keyCode);
        }
      } 
    }
  }
}

bool PS3Keyboard::keyState(char keyCode) {
  return keyStates_[keyCode];
}

void PS3Keyboard::setKeydownListener(IKeyboardListener* keyDownListener) {
  keyDownListener_ = keyDownListener;
}
