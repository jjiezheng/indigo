#include "standard.hlsl"

uniform	float3 DiffuseColor;
uniform	float3 AmbientColor;

uniform float DiffusePower;
uniform float SpecularPower;
uniform float SpecularIntensity;

uniform	float3x3 NormalMatrix;
uniform	float4x4 WorldViewProj;
uniform	float4x4 WorldView;
uniform	float4x4 World;

uniform float Far = 200.0f;
uniform float Near = 1.0f;


struct VOutput {
	float4 position			: SV_POSITION;
	float3 normal			: TEXCOORD0;
	float3 depth			: TEXCOORD1;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
	OUT.normal = normal.xyz;
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
		   float3 depth 			: TEXCOORD1) {
	POutput OUT;
	
	OUT.color = float4(DiffuseColor, 1);					
	OUT.normal = float4(normal, 1);

	float depthNDC = depth.x / depth.y; // z / w
	float depthLinear = (-depth.z - Near) / (Far - Near);
	OUT.depth = float4(depthNDC, depthLinear, 0, DiffusePower);
	
	return OUT;
}

technique11 Test {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}