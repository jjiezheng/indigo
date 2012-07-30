#include "standard.hlsl"

uniform float2 NoiseScale;
uniform float Radius;

uniform int KernelSize;
uniform float4 Kernel[16];

Texture2D NoiseMap;
SamplerState NoiseMapSamplerState {
	AddressU = Wrap;
    AddressV = Wrap;
};

Texture2D NormalMap;
SamplerState NormalMapSamplerState {
	AddressU = Clamp;
    AddressV = Clamp;
};

Texture2D DepthMap;
SamplerState DepthMapSamplerState {
	AddressU = Clamp;
    AddressV = Clamp;
};

uniform float4x4 Projection;
uniform float4x4 WorldViewProj;
uniform float4x4 ProjInv;
uniform float4x4 ViewInv;
uniform float4x4 ViewProj;
uniform float4x4 ViewProjInv;

struct VOutput {
      float4 position 			: SV_POSITION;
      float4 texCoord		: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		   float4 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}
float4 ps(float4 position 		: SV_POSITION,
		  float4 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen;
	positionScreen.xy = (texCoord.xy * 2.0f) - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth; 
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float4 positionWorldRaw = mul(ViewProjInv, positionScreen);
	float4 positionWorld = positionWorldRaw / positionWorldRaw.w;	

	return positionWorld;

	// SSAO
	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	randomNormal = normalize(randomNormal);

	float occlusion = 0.0f;
	float radius = 0.1f;

	float3 tangent = normalize(randomNormal - (normal * dot(randomNormal, normal)));
	float3 bitangent = cross(normal, tangent);
	float3x3 tbn = float3x3(bitangent, tangent,  normal);

	// right up to here
	for (int i = 0; i < KernelSize; i++) {	
		float3 sample = mul(tbn, Kernel[i].xyz);
		sample = (sample * radius) + positionView;

		float4 offset = float4(sample, 1.0f);
		offset = mul(Projection, offset);
		offset = offset / offset.w;

		offset.xy = (offset.xy * 0.5f) + 0.5f;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, offset);
		float depthDifference = abs(depth - sampleDepth);

		//return float4(sample, 1.0f);

		if (depthDifference < radius && sampleDepth > depth) {
			occlusion += 0.6f;
		}
	}

	occlusion = 1.0f - (occlusion / 16.0f);

	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
