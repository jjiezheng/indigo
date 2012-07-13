BlendState Add {
	BlendEnable[0] = true;
    SrcBlend = One;
    DestBlend = One;
    BlendOp = ADD;
    RenderTargetWriteMask[0] = 0x0F;
};

BlendState NoBlend {
	BlendEnable[0] = false;
};