#define FXAA_PC 1
#define FXAA_HLSL_4 1
#define FXAA_QUALITY__PRESET 15
#include "Fxaa3_11.h"

#include "standard.hlsl"

Texture2D FinalMap;
SamplerState FinalMapSamplerState {
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
	FxaaTex tex;
	tex.smpl = FinalMapSamplerState;
	tex.tex = FinalMap;

	float4 origin = float4(0.0f, 0.0f, 0.0f, 1.0f);

	return FxaaPixelShader(
		texCoord, origin, tex, tex, tex, ScreenSizeInv, 
		origin, origin, origin,
		1.0f, 0.063f, 0.0312f, 2.0f, 
		0.0f, 0.0f, origin);
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
