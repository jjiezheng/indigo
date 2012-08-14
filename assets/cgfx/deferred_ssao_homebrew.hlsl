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

};

uniform float4x4 Projection;
uniform float4x4 ProjInv;

uniform float4x4 ViewProjInv;
uniform float4x4 View;

uniform float TanHalfFOV;
uniform float AspectRatio;

struct VOutput {
      float4 position 		: SV_POSITION;
      float2 texCoord		: TEXCOORD0;
      float3 viewRay		: TEXCOORD1;
};

VOutput vs(float4 position 	: POSITION,
		   float2 texCoord 	: TEXCOORD0) {
    VOutput OUT;
    OUT.position = position;
    OUT.texCoord = texCoord;
    OUT.viewRay = float3(position.x * TanHalfFOV * AspectRatio, position.y * TanHalfFOV, 1.0f);
    return OUT;
}

float4 ps(float4 position 		: SV_POSITION,
		  float2 texCoord 		: TEXCOORD0,
		  float3 viewRay 		: TEXCOORD1) : SV_TARGET0 {
	float4 normalData = NormalMap.Sample(NormalMapSamplerState, texCoord);
	float3 normal = normalize(normalData.xyz);

	float3 depth = DepthMap.Sample(DepthMapSamplerState, texCoord);

	float4 positionScreen = float4(0, 0, 0, 1);
	positionScreen.xy = texCoord.xy * 2.0f - 1.0f;
	positionScreen.y = -positionScreen.y;
	positionScreen.z = depth.x;
	positionScreen.w = 1.0f;

	float4 positionViewRaw = mul(ProjInv, positionScreen);
	float4 positionView = positionViewRaw / positionViewRaw.w;

	return float4(depth.z, positionView.z, 0, 1);

	float4 linearPositionDepth = (-positionView.z - 1.0f) / (200.0f - 1.0f); 

	return float4(depth.x, positionView.z, depth.z, 1);

	float3 bitangent = float3(0.0f, 1.0f, 0.0f);

	if (dot(normal, bitangent) == 1) {
		bitangent = float3(0, 0, -1);
	} 

	float3 tangent = cross(bitangent, normal);
	bitangent = cross(normal, tangent);

	float3x3 normalBasis = float3x3(tangent, bitangent, normal);

	float occlusionContribution = 0;

	float radius = 1.0;

	float4 samples[] = {{0, -0.0, 0.0, 1}};

	for (int i = 0; i < 1; i++) {
		float3 sample = samples[i].xyz;

		float3 sampleAtNormalBasis = mul(sample, normalBasis) * radius;
		float3 sampleAtViewPosition = positionView + sampleAtNormalBasis;
		float sampleAtViewPositionZ = (-sampleAtViewPosition.z - 1.0f) / (200.0f - 1.0f);

		//return float4(positionView.xy, sampleAtViewPosition.xy);

		float4 sampleScreenRaw = mul(Projection, sampleAtViewPosition);
		float4 sampleScreen = sampleScreenRaw / sampleScreenRaw.w;

		float4 sampleTexCoord = float4(0, 0, 0, 1);
		sampleTexCoord.xy = (sampleScreen.xy * 0.5f) + 0.5f;
		sampleTexCoord.y = 1.0f - sampleTexCoord.y;

		float sampleDepth = DepthMap.Sample(DepthMapSamplerState, sampleTexCoord).y;

		

		//float sampleAtViewPositionZ = (-sampleAtViewPosition.z - 1.0f) / (200.0f - 1.0f);

		//return float4(sampleAtViewPosition.z, sampleAtViewPosition.z, sampleAtViewPosition.z, 1.0f);

		

		// these dpeths come out less than each other, regardless that they are sitting on the sample plane, this is wrong

		//return float4(sample, 1.0f);

		//return float4(sampleDepth, sampleAtViewPositionZ, 0.0f, 1.0f);

		//occlusionContribution += sampleDepth < sampleAtViewPositionZ ? 1.0f : 0.0f;

		//float rangeCheck = abs(depth - sampleDepth) < radius;
		//occlusionContribution += rangeCheck * sampleDepth < sampleAtViewPositionZ ? 1.0f : 0.0f;
	}

	float occlusion =  1.0f - (occlusionContribution / 1);
	return float4(occlusion, occlusion, occlusion, 1.0f);
}


technique11 Main {
	pass P0 {
		SetVertexShader(CompileShader(vs_4_0, vs()));
		SetPixelShader(CompileShader(ps_4_0, ps()));
		SetBlendState(NoBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	}
}