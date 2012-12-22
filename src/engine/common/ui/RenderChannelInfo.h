#ifndef RENDERCHANNELINFO_H
#define RENDERCHANNELINFO_H

#include "renderer/Control.h"

class Label;
class IRenderChannelInfoService;

class RenderChannelInfo : public Control {

public:

	static RenderChannelInfo* info(IRenderChannelInfoService* infoService);

public:

	RenderChannelInfo(IRenderChannelInfoService* infoService)
		: infoService_(infoService) { }

private:

	void init();

public:

	void render(const Matrix4x4& projection);

	void update(float dt);

private:

	Label* label_;
	IRenderChannelInfoService* infoService_;

};

#endif
