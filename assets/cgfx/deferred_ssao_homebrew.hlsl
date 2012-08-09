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
	Filter = MIN_MAG_MIP_LINEAR;
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

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float depth = DepthMap.Sample(DepthMapSamplerState, texCoord).r;
	float depthHigh = DepthMap.Sample(DepthMapSamplerState, texCoord).g;

	if (depth == 1.0f || depth == 0.0f) {
		return float4(0, 0, 0, 1);
	}

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float3 bitangent = float3(0.0f, 1.0f, 0.0f);

	if (dot(normal, bitangent) == 1) {
		bitangent = float3(0, 0, -1);
	} 

	float3 tangent = cross(bitangent, normal);
	bitangent = cross(normal, tangent);

	float3x3 normalBasis = float3x3(tangent, bitangent, normal);

	float occlusionContribution = 0;

	int sampleSize = 1;

	float3 samples[] = {
		{0, -0.01, 0.01}
	};

	float radius = 1;

	for (int i = 0; i < sampleSize; i++) {
		float3 sample = samples[i].xyz;
		float3 sampleAtNormalBasis = mul(sample, normalBasis);
		float3 sampleAtViewPosition = positionView + sampleAtNormalBasis;

		float4 sampleScreenRaw = mul(Projection, sampleAtViewPosition);
		float4 sampleScreen = sampleScreenRaw / sampleScreenRaw.w;

		float4 sampleTexCoord = float4(0, 0, 0, 1);
		sampleTexCoord.xy = (sampleScreen.xy * 0.5f) + 0.5f;
		sampleTexCoord.y = 1.0f - sampleTexCoord.y;

		float sampleDepthHigh = DepthMap.Sample(DepthMapSamplerState, sampleTexCoord).g;

		return float4(sampleDepthHigh, depthHigh, depthHigh - sampleDepthHigh, 1.0f);

		if (depthHigh - sampleDepthHigh > 0) {
			occlusionContribution += 1;
		}
	}

	float occlusion = 1.0f - (occlusionContribution / sampleSize);
	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}