#include "utils.cg"

Texture2D ColorMap;
SamplerState ColorMapSamplerState { };

Texture2D NormalMap;
SamplerState NormalMapSamplerState { };

uniform float4x4 WorldViewProj;

uniform float4 DiffuseColor;

uniform float DiffusePower;
uniform float SpecularPower;
uniform float SpecularIntensity;

struct VOutput {
	float4 position			: SV_POSITION;
	float3 normal			: TEXCOORD0;
	float2 texCoord			: TEXCOORD1;
	float2 depth			: TEXCOORD2;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.texCoord = texCoord;
	OUT.normal = normal.xyz;
	OUT.depth.x = OUT.position.z;
	OUT.depth.y = OUT.position.w;
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
		   float2 depth 			: TEXCOORD2) {
	POutput OUT;
	
	OUT.color = ColorMap.Sample(ColorMapSamplerState, texCoord);				
	OUT.color = float4(OUT.color.a, OUT.color.a, OUT.color.a, OUT.color.a);	
	OUT.normal = float4(normalize(normal), 1.0f);// NormalMap.Sample(NormalMapSamplerState, texCoord);

	float depthHom = depth.x / depth.y; // z / w
	OUT.depth = float4(depthHom, SpecularPower, SpecularIntensity, DiffusePower);

	return OUT;
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
