#include "GameUI.h"

#include "ui/FPSStats.h"
#include "ui/RenderChannelInfo.h"
#include "ui/UIMouse.h"

#include "renderer/GraphicsInterface.h"

void GameUI::init(IRenderChannelInfoService* renderChannelInfoService) {
  ui_.init(GraphicsInterface::backBufferSize());

//   UIMouse* uiMouse = UIMouse::mouse("ui/aero_arrow.png");
//   ui_.addControl(uiMouse);

  FPSStats* fpsStats = FPSStats::stats();
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
