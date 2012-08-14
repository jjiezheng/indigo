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
SamplerState DepthMapSamplerState {
	AddressU = Clamp;
    AddressV = Clamp;
};

uniform float4x4 Projection;
uniform float4x4 ProjInv;

uniform float4x4 ViewProjInv;
uniform float4x4 View;

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

bool cmpa(float3 v1, float3 v2) {
	float3 result = v1 && v2;
	return result.x && result.y && result.z;
}

float linearizeDepth(float depth, float4x4 projMatrix) {
	return projMatrix[3][2] / (depth - projMatrix[2][2]);
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;
	float depthMeters = DepthMap.Sample(DepthMapSamplerState, texCoord).r * 100;
	float depthHigh = DepthMap.Sample(DepthMapSamplerState, texCoord).g;
	float depthProj = DepthMap.Sample(DepthMapSamplerState, texCoord).b;

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float2 noiseTexCoords = texCoord * NoiseScale;
	float3 rvec = NoiseMap.Sample(NoiseMapSamplerState, noiseTexCoords).rgb * 2.0 - 1.0;
	float3 tangent = normalize(rvec - normal * dot(rvec, normal));
	float3 bitangent = cross(tangent, normal);
	float3x3 normalBasis = float3x3(tangent, bitangent, normal);

	float occlusionContribution = 0;

	float radius = 0.3;

	for (int i = 0; i < KernelSize; i++) {
		float3 sample = Kernel[i].xyz * radius;
		sample = mul(sample, normalBasis);

		float3 samplePos = float3(texCoord, depth);
		samplePos += sample;


		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, samplePos.xy).r * 100;

		float rangeIsInvalid = saturate(depthMeters - sampleDepth);
		occlusionContribution += lerp(sampleDepth > samplePos.z, 0.5, rangeIsInvalid);
	}

	float occlusion = (occlusionContribution / KernelSize);
	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}