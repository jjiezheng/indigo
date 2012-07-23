#include "standard.hlsl"

Texture2D SourceMap;
SamplerState SourceMapSamplerState;

float2 TexelSize;

struct VOutput {
      float4 position 			: SV_POSITION;
      float2 texCoord			: TEXCOORD0;
};

VOutput vs(float4 position : POSITION,
		   float2 texCoord : TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord		: TEXCOORD0) : SV_TARGET0 {
	//return SourceMap.Sample(SourceMapSamplerState, texCoord).r;
	float4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			float2 offset = float2(TexelSize.x * float(j), TexelSize.y * float(i));
			result += SourceMap.Sample(SourceMapSamplerState, texCoord + offset).r;
		}
	}
	
	result = result * 0.0625;

	return result;
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}

