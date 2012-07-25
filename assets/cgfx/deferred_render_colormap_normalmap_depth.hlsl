#include "utils.cg"

Texture2D ColorMap;
SamplerState ColorMapSamplerState {
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState {
};

uniform float4x4 WorldViewProj;

struct VOutput {
	float4 position			: SV_POSITION;
	float3 normal			: TEXCOORD0;
	float2 texCoord			: TEXCOORD1;
	float depth				: TEXCOORD2;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.texCoord = texCoord;
	OUT.depth = OUT.position.z / OUT.position.w;
	OUT.normal = normal.xyz;
 	return OUT;
}

struct POutput {
	float4 color 	: SV_TARGET0;
	float4 normal 	: SV_TARGET1;
	float4 depth 	: SV_TARGET2;
};

POutput ps(float4 position			: SV_POSITION,
		   float3 normal			: TEXCOORD0,
		   float2 texCoord			: TEXCOORD1,
		   float  depth 			: TEXCOORD2) {
	POutput OUT;
	OUT.color = ColorMap.Sample(ColorMapSamplerState, texCoord);					
	OUT.normal = NormalMap.Sample(NormalMapSamplerState, texCoord);
	OUT.depth = float4(depth, depth, depth, 1);
	return OUT;
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
