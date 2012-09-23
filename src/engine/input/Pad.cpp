#include "Pad.h"

#ifdef PLATFORM_PS3
#include <cell/pad.h>    
#endif

#include "io/Log.h"

#include <stdio.h>

#define MAX_PAD 1

float Pad::leftStickY_ = 0;

void Pad::update() {
#ifdef PLATFORM_PS3
  static CellPadInfo2 padInfo;
  int32_t ret;
  if ((ret = cellPadGetInfo2(&padInfo)) != CELL_OK) {
    //printf("Error(%08X) : cellPadGetPadInfo2\n", ret);
    return;
  }

  static CellPadData padData;

  for (int i = 0; i < MAX_PAD; i++) {
    ret = cellPadGetData (i, &padData);

    if (0 != ret) {
      continue;
    }

    if (padData.len > 0) {
      int padValue = 255 - padData.button[7];
      float leftStickYRaw = padValue / 255.0f;
      float leftStickY = (leftStickYRaw * 2.0f) - 1.0f;

      printf("%f", leftStickY);

      if (leftStickY > 0.1f || leftStickY < -0.1f) {
        leftStickY_ = leftStickY;
      } 
      else {
        leftStickY_ = 0.0f;
      }
    }
  }
#endif
}

float Pad::leftStickY() {
  return leftStickY_;
}

void Pad::init() {
#ifdef PLATFORM_PS3
  int32_t ret = cellPadInit(MAX_PAD);
  if (ret != CELL_OK) {
    LOG(LOG_CHANNEL_INPUT, "Failed to init pad");
  }
#endif
}

float Pad::leftStickX() {
  return 0;
}
