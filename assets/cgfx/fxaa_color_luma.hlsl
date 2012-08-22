#include "standard.hlsl"

Texture2D InputMap;
SamplerState InputMapSamplerState {
	Filter = MIN_MAG_MIP_LINEAR;
};

uniform float4 ScreenSizeInv;

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
	float3 color = InputMap.Sample(InputMapSamplerState, texCoord).rgb;
	float luma =  dot(color, float3(0.299f, 0.587f, 0.114f));
	return float4(color, luma);
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
