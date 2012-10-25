#include "RenderChannelInfo.h"

#include <sstream>

#include "services/IRenderChannelInfoService.h"

#include "renderer/Label.h"

RenderChannelInfo* RenderChannelInfo::info(IRenderChannelInfoService* infoService) {
	RenderChannelInfo* info = new RenderChannelInfo(infoService);
	info->init();
	return info;
}

void RenderChannelInfo::init() {
	label_ = Label::labelWithFont("fonts/arial.fnt");
	label_->setPosition(0, 2);
}

void RenderChannelInfo::render(const Matrix4x4& projection) {
	label_->render(projection);
}

void RenderChannelInfo::update(float dt) {
	std::string activeChannel = infoService_->getActiveRenderChannel();

	std::stringstream labelText;
	labelText << "Presenting " << activeChannel;

	label_->setText(labelText.str());
}
