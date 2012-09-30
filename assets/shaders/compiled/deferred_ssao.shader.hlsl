#include "standard.h"

uniform float Radius;
uniform float KernelSize;
uniform float2 NoiseScale;
uniform float4 Kernel[16];

uniform float Far;
uniform float Near;

 sampler2D NoiseMap;
// SamplerState NoiseMapSamplerState {
// 	AddressU = Wrap;
//     AddressV = Wrap;
// };

sampler2D NormalMap : TEXUNIT0;
sampler2D DepthMap : TEXUNIT1;

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
	float4 normalData = tex2D(NormalMap, texCoord);
	float3 normal = normalize(normalData.xyz);

	float3 depth = tex2D(DepthMap, texCoord);

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth.x;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	float2 noiseTexCoords = texCoord * NoiseScale;
	float3 rvec = tex2D(NoiseMap, noiseTexCoords).rgb ;
	float3 tangent = normalize(rvec - normal * dot(rvec, normal));
	float3 bitangent = cross(tangent, normal);
	float3x3 normalBasis = float3x3(tangent, bitangent, normal);

	float occlusionContribution = 0;

	for (int i = 0; i < KernelSize; i++) {
		float3 sample = Kernel[i].xyz * Radius;

		float3 sampleAtNormalBasis = mul(sample, normalBasis);
		float3 sampleAtViewPosition = positionView + sampleAtNormalBasis;
		float sampleAtViewPositionZ = (-sampleAtViewPosition.z - Near) / (Far - Near);

		float4 sampleScreenRaw = mul(Projection, float4(sampleAtViewPosition, 1));
		float4 sampleScreen = sampleScreenRaw / sampleScreenRaw.w;

		float2 sampleTexCoord = (sampleScreen.xy * 0.5f) + 0.5f;
		sampleTexCoord.y = 1.0f - sampleTexCoord.y;

		float sampleDepth = tex2D(DepthMap, sampleTexCoord).y;

		float rangeCheck = abs(depth.y - sampleDepth) < Radius * 0.001 ? 1.0 : 0.0;
		occlusionContribution += (sampleDepth <= sampleAtViewPositionZ ? 1.0 : 0.0) * rangeCheck;
	}

	float occlusion = 1.0f - (occlusionContribution / KernelSize);
	return float4(occlusion, occlusion, occlusion, 1.0f);
}