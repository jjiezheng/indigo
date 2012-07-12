BlendState SrcAlphaBlendingAdd {
	BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = INV_SRC_ALPHA;
    BlendOp = ADD;

    RenderTargetWriteMask[0] = 0x0F;
};
