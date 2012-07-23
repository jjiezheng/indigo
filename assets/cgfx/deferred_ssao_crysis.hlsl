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
SamplerState NormalMapSamplerState;

Texture2D DepthMap;
SamplerState DepthMapSamplerState;

uniform float4x4 Projection;
uniform float4x4 WorldViewProj;
uniform float4x4 ProjInv;
uniform float4x4 ViewInv;
uniform float4x4 ViewProj;
uniform float4x4 ViewProjInv;

struct VOutput {
      float4 position 		: SV_POSITION;
      float2 texCoord		: TEXCOORD0;
};

VOutput vs(float4 position 	: POSITION,
		   float2 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalData.xyz;

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen;
	positionScreen.xy = (texCoord.xy * 2.0f) - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth; 
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float4 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);

	float radius = 0.06f;
	float occlusionContribution = 0.8f;

	float occlusion = 0.0f;

	for (int i = 0; i < KernelSize; i++) {
		float3 sample = reflect(Kernel[i].xyz, randomNormal) * radius;

		float4 viewSample = positionView + float4(sample, 1.0f);

		float4 offset = mul(Projection, viewSample);
		offset /= offset.w;

		offset.xy = (offset.xy * 0.5) + 0.5;
		offset.y = 1.0f - offset.y;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, offset);
		float depthDifference = abs(sampleDepth - depth);

		if (depthDifference < radius && sampleDepth <= depth) {
			occlusion += occlusionContribution;
		}
		
	}

	float occlusionOutput = 1.0f - (occlusion / KernelSize);

	return float4(occlusionOutput, occlusionOutput, occlusionOutput, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
