#include "standard.hlsl"

uniform float2 TexelSize;

Texture2D SourceMap;
SamplerState SourceMapSamplerState;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 screenPosition		: TEXCOORD0;
};

VOutput vs(float4 position : POSITION) {
    VOutput OUT;
    OUT.position = position;
    OUT.screenPosition = OUT.position;
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float4 screenPosition	: TEXCOORD0) : SV_TARGET0 {
	float3 screenPositionHom = screenPosition.xyz / screenPosition.w;
	float2 texCoord = contract(screenPosition);

	float result = 0.0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float2 offset = float2(TexelSize.x * float(j), TexelSize.y * float(i));
			result += SourceMap.Sample(SourceMapSamplerState, texCoord + offset).r;
		}
	}
	
	result = result * 0.0625;
	return float4(result, result, result, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}

