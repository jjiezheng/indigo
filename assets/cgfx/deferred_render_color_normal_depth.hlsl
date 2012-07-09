#include "utils.cg"

cbuffer Uniforms : register(b0) {
	float3 DiffuseColor;
	float3 AmbientColor;
	float3x3 NormalMatrix;
	float4x4 WorldViewProj;
	float4x4 World;
}

struct VOutput {
	float4 position			: POSITION;
	float3 normal			: TEXCOORD0;
	float2 depth			: TEXCOORD1;
};

VOutput vs(float4 position 		: POSITION,
		   float4 normal 		: NORMAL) {
	VOutput OUT;
	OUT.position = mul(WorldViewProj, position);
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

POutput ps(float3 normal			: TEXCOORD0,
		   float2 depth 			: TEXCOORD1) {
	POutput OUT;
	OUT.color = float4(DiffuseColor, 1);					
	OUT.normal = float4(normal, 1);
	float depthHom = depth.x / depth.y; // z / w
	OUT.depth = float4(depthHom, depthHom, depthHom, 1);
	return OUT;
}