#include "PS3Pad.h"

#include "platform/PlatformDefs.h"

#include <cell/pad.h>

#include "io/Log.h"

#include <stdio.h>

#define MAX_PAD 1

float stickValue(CellPadData padData, int padIndex) {
  int padValue = 255 - padData.button[padIndex];
  float stickRaw = padValue / 255.0f;
  float stick = (stickRaw * 2.0f) - 1.0f;
  return stick > 0.2f || stick < -0.2f ? stick : 0.0f;
}

void PS3Pad::setup() {
  int32_t ret = cellPadInit(MAX_PAD);
  if (ret != CELL_OK) {
    LOG(LOG_CHANNEL_INPUT, "Failed to init pad");
  }
}

void PS3Pad::update() {
  static CellPadInfo2 padInfo;
  int32_t ret;
  if ((ret = cellPadGetInfo2(&padInfo)) != CELL_OK) {
    return;
  }

  static CellPadData padData;

  for (int i = 0; i < MAX_PAD; i++) {
    ret = cellPadGetData(i, &padData);

    if (0 != ret) {
      continue;
    }

    if (padData.len > 0) {
      rightStickX_ = stickValue(padData, 4);
      rightStickY_ = stickValue(padData, 5);
      leftStickX_ = -stickValue(padData, 6);
      leftStickY_ = stickValue(padData, 7);

      int buttonData = padData.button[3];
      leftShoulder_ = buttonData & CELL_PAD_CTRL_L1;
      rightShoulder_ = buttonData & CELL_PAD_CTRL_R1;
    }
  }
}

float PS3Pad::leftStickY() {
  return leftStickY_;
}

float PS3Pad::leftStickX() {
  return leftStickX_;
}

float PS3Pad::rightStickX() {
  return rightStickX_;
}

float PS3Pad::rightStickY() {
  return rightStickY_;
}

bool PS3Pad::leftShoulder() {
  return leftShoulder_;
}

bool PS3Pad::rightShoulder() {
  return rightShoulder_;
}
