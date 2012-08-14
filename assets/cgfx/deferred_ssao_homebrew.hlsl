#include "standard.hlsl"

uniform float Radius;
uniform float KernelSize;
uniform float2 NoiseScale;
uniform float4 Kernel[16];

uniform float Far = 200.0f;
uniform float Near = 1.0f;

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

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	//normalData = mul(View, normalData);
	float3 normal = normalize(normalData.xyz);

	float3 depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth.x;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float2 noiseTexCoords = texCoord * NoiseScale;
	float3 rvec = NoiseMap.Sample(NoiseMapSamplerState, noiseTexCoords).rgb ;
	float3 tangent = normalize(rvec - normal * dot(rvec, normal));
	float3 bitangent = cross(tangent, normal);
	float3x3 normalBasis = float3x3(tangent, bitangent, normal);

	float occlusionContribution = 0;

	for (int i = 0; i < KernelSize; i++) {
		float3 sample = Kernel[i].xyz * Radius;

		float3 sampleAtNormalBasis = mul(sample, normalBasis);
		float3 sampleAtViewPosition = positionView + sampleAtNormalBasis;
		float sampleAtViewPositionZ = (-sampleAtViewPosition.z - Near) / (Far - Near);

		float4 sampleScreenRaw = mul(Projection, sampleAtViewPosition);
		float4 sampleScreen = sampleScreenRaw / sampleScreenRaw.w;

		float4 sampleTexCoord = float4(0, 0, 0, 1);
		sampleTexCoord.xy = (sampleScreen.xy * 0.5f) + 0.5f;
		sampleTexCoord.y = 1.0f - sampleTexCoord.y;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, sampleTexCoord).y;

		float rangeIsInvalid = abs(depth.y - sampleDepth);
		if (depth.x < 1.0f) {
			occlusionContribution += lerp(sampleDepth < sampleAtViewPositionZ, 0.5, rangeIsInvalid);
		}
	}

	float occlusion = 1.0f - (occlusionContribution / KernelSize);
	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}