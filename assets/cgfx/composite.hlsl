#include "standard.hlsl"

Texture2D ColorMap;
SamplerState ColorMapSamplerState { };

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

float4 ps(float4 position			: SV_POSITION,
		   float2 texCoord			: TEXCOORD0) : SV_TARGET0 {
	float4 color = ColorMap.Sample(ColorMapSamplerState, texCoord);				
	return color;
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(Add, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
