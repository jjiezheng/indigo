#include "utils.cg"

Texture2D ColorMap;
SamplerState ColorMapSamplerState { };

Texture2D NormalMap;
SamplerState NormalMapSamplerState { };

uniform float4x4 WorldViewProj;
uniform float4x4 WorldView;
uniform float4x4 NormalMatrix;

uniform float4 DiffuseColor;

uniform float DiffusePower;
uniform float SpecularPower;
uniform float SpecularIntensity;

uniform float Far = 200.0f;
uniform float Near = 1.0f;

struct VOutput {
	float4 position			: SV_POSITION;
	float3 normal			: TEXCOORD0;
	float2 texCoord			: TEXCOORD1;
	float3 depth			: TEXCOORD2;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL,
		   float2 texCoord 		: TEXCOORD0) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.normal = normalize(mul(NormalMatrix, normal.xyz).xyz);
	OUT.texCoord = texCoord;
	
	OUT.depth.x = OUT.position.z;
	OUT.depth.y = OUT.position.w;

	float4 positionView = mul(WorldView, position);
 	OUT.depth.z = positionView.z;
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
		   float3 depth 			: TEXCOORD2) {
	POutput OUT;
	
	OUT.color = ColorMap.Sample(ColorMapSamplerState, texCoord);				
	OUT.normal = float4(normal, DiffusePower);

	float depthNDC = depth.x / depth.y; // z / w
	float depthLinear = (-depth.z - Near) / (Far - Near);
	OUT.depth = float4(depthNDC, depthLinear, SpecularPower, SpecularIntensity);

	return OUT;
}

technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
	}
}
