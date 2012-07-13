#include "standard.hlsl"

Texture2D Texture;
SamplerState TextureSampler {
	Filter = MIN_MAG_MIP_LINEAR;
};

struct VOutput {
	float4 position			: SV_POSITION;
	float2 texCoord			: TEXCOORD0;
};

VOutput vs(float4 position 		: POSITION,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = position;
	OUT.texCoord = texCoord;
 	return OUT;
}

float4 ps(float4 position : SV_POSITION,
		  float2 texCoord : TEXCOORD0) : SV_TARGET0 {
	return Texture.Sample(TextureSampler, texCoord);
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
