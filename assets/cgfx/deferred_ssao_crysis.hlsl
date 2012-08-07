#include "standard.hlsl"

uniform float Radius;
uniform float KernelSize;
uniform float2 NoiseScale;
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
uniform float4x4 ProjInv;

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

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;


	float4 positionScreen;
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float3 randomNormal = NoiseMap.Sample(NoiseMapSamplerState, texCoord * NoiseScale);
	randomNormal = normalize(randomNormal);

	float radius = 0.31f;
	float occlusionContribution = 1.0f;
	float occlusion = 0.0f;

	float3 tangent = normalize(randomNormal - normalize(normal) * dot(randomNormal, normalize(normal)));
	float3 bitangent = cross(normalize(normal), tangent);

	float3x3 tbn = float3x3(tangent, bitangent, normalize(normal));


	for (int i = 0; i < KernelSize; ++i) {
		float3 sample = mul(tbn, Kernel[i].xyz) * radius;

		float4 viewSample = float4(positionView.xyz + sample, 1.0f);

		float4 offset = mul(Projection, viewSample);
		offset /= offset.w;

		offset = (offset * 0.5f) + 0.5f;
		offset.y = 1.0f - offset.y;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, offset).r;

		float4 sampleScreen;
		sampleScreen.xy = offset.xy * 2.0f - 1.0f;
		sampleScreen.y = -sampleScreen.y;
		sampleScreen.z = sampleDepth;
		sampleScreen.w = 1.0f;

		float4 sampleViewRaw = mul(ProjInv, sampleScreen);
		float4 sampleView = sampleViewRaw / sampleViewRaw.w;

		float depthDifference = abs(positionView.z - sampleView.z);

		// so the issue is: comparing the depth values. creates issues with flat lying geometry. can this be smoothed out?!

		if (depthDifference < radius){//} && depth > 0.0f && depth < 1.0f) {
			if (sampleDepth <= depth) {
				occlusion += occlusionContribution;
			}
		}
	}

	float strength = 1.0f;
	float occlusionOutput =  1.0f - ((occlusion / KernelSize) * strength);
	return float4(occlusionOutput, occlusionOutput, occlusionOutput, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}
