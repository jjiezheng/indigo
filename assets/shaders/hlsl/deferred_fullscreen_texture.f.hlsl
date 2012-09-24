Texture2D Texture;
SamplerState TextureSampler {
	Filter = MIN_MAG_MIP_LINEAR;
};

float4 ps(float4 position : SV_POSITION,
		  float2 texCoord : TEXCOORD0) : SV_TARGET0 {
	return Texture.Sample(TextureSampler, texCoord);
}