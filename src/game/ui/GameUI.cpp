#include "GameUI.h"

#include "ui/FPSStats.h"
#include "ui/RenderChannelInfo.h"
#include "ui/UIMouse.h"
#include "ui/UILine.h"

#include "renderer/GraphicsInterface.h"

#include "input/KeyboardState.h"

static const int MOUSE_TAG = 101;
static const int FPS_LABEL_TAG = 102;

void GameUI::init(IRenderChannelInfoService* renderChannelInfoService) {
	ui_.init(GraphicsInterface::backBufferSize());

//   UIMouse* uiMouse = UIMouse::mouse("ui/aero_arrow.dds");
//   uiMouse->setTag(MOUSE_TAG);
//   ui_.addControl(uiMouse);

	FPSStats* fpsStats = FPSStats::stats();
  fpsStats->setTag(FPS_LABEL_TAG);
	ui_.addControl(fpsStats);

	RenderChannelInfo* renderChannelInfo = RenderChannelInfo::info(renderChannelInfoService);
	ui_.addControl(renderChannelInfo);
}

void GameUI::render() {
  ui_.render();
} 

void GameUI::update(float dt) {
  ui_.update(dt);
}

void GameUI::destroy() {
	ui_.destroy();
}

void GameUI::showMouse(bool isShowing) {
 	Control* control = ui_.findControlByTag(MOUSE_TAG);
 	UIMouse* mouse = static_cast<UIMouse*>(control);
 	mouse->setVisible(isShowing);
}

void GameUI::keyUp(int keyCode) {
  if (KEY_F1 == keyCode) {
    Control* control = ui_.findControlByTag(FPS_LABEL_TAG);
    control->toggleVisible();
  }
}